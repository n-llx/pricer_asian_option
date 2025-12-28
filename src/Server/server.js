const http = require('http');
const { spawn } = require('child_process');
const path = require('path');

const PORT = 18080;
const ADAPTER_PATH = path.resolve(__dirname, '../../build/bin/PricerAdapter.exe');

const server = http.createServer((req, res) => {
    // CORS headers
    res.setHeader('Access-Control-Allow-Origin', '*');
    res.setHeader('Access-Control-Allow-Methods', 'POST, OPTIONS');
    res.setHeader('Access-Control-Allow-Headers', 'Content-Type');

    if (req.method === 'OPTIONS') {
        res.writeHead(204);
        res.end();
        return;
    }

    if (req.url === '/api/price' && req.method === 'POST') {
        let body = '';
        req.on('data', chunk => {
            body += chunk.toString();
        });
        req.on('end', () => {
            // Spawn C++ Adapter
            const pricer = spawn(ADAPTER_PATH);

            let output = '';
            let errorOutput = '';

            pricer.stdout.on('data', (data) => {
                output += data.toString();
            });

            pricer.stderr.on('data', (data) => {
                errorOutput += data.toString();
                console.error(`C++ Error: ${data}`);
            });

            pricer.on('close', (code) => {
                if (code !== 0) {
                    res.writeHead(500, { 'Content-Type': 'text/plain' });
                    res.end(`Calculation Error: ${errorOutput || 'Unknown error'}`);
                } else {
                    res.writeHead(200, { 'Content-Type': 'application/json' });
                    res.end(output);
                }
            });

            pricer.on('error', (err) => {
                console.error("Failed to start adapter:", err);
                res.writeHead(500, { 'Content-Type': 'text/plain' });
                res.end(`Server Error: Failed to start C++ adapter at ${ADAPTER_PATH}`);
            });

            // Write input to C++ stdin
            pricer.stdin.write(body);
            pricer.stdin.end();
        });
    } else {
        res.writeHead(404, { 'Content-Type': 'text/plain' });
        res.end('Not Found');
    }
});

server.listen(PORT, () => {
    console.log(`Node.js Logic Server running on http://localhost:${PORT}`);
    console.log(`Using C++ Adapter: ${ADAPTER_PATH}`);
});
