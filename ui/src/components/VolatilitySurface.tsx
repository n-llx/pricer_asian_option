import React from 'react';
import Plot from 'react-plotly.js';

interface VolatilitySurfaceProps {
    data: {
        x: number[]; // Strikes or Spot
        y: number[]; // Maturities or Vol
        z: number[][]; // Prices or Implied Vol
    } | null;
}

export function VolatilitySurface({ data }: VolatilitySurfaceProps) {
    if (!data) {
        return (
            <div className="h-[400px] w-full bg-slate-950/50 rounded-xl border border-slate-800 flex items-center justify-center text-slate-500">
                Run calculation to generate surface
            </div>
        );
    }

    return (
        <div className="w-full h-[400px] rounded-xl overflow-hidden border border-slate-800 bg-slate-900">
            <Plot
                data={[
                    {
                        x: data.x,
                        y: data.y,
                        z: data.z,
                        type: 'surface',
                        colorscale: 'Viridis',
                        showscale: false,
                    },
                ]}
                layout={{
                    autosize: true,
                    title: { text: 'Volatility Surface', font: { color: '#ffffff' } },
                    paper_bgcolor: '#0f172a',
                    plot_bgcolor: '#0f172a',
                    margin: { l: 0, r: 0, b: 0, t: 40 },
                    scene: {
                        xaxis: { title: 'Spot', color: '#94a3b8' },
                        yaxis: { title: 'Vol', color: '#94a3b8' },
                        zaxis: { title: 'Price', color: '#94a3b8' },
                        camera: { eye: { x: 1.5, y: 1.5, z: 1.5 } }
                    }
                }}
                useResizeHandler={true}
                style={{ width: "100%", height: "100%" }}
            />
        </div>
    );
}
