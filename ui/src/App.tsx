```javascript
import { useState } from 'react';
import { Card } from './components/Card';
import { InputParam } from './components/InputParam';
import { GreeksDisplay } from './components/GreeksDisplay';
import { VolatilitySurface } from './components/VolatilitySurface';
import { Play } from 'lucide-react';

function App() {
  const [params, setParams] = useState({
    S0: 100,
    K: 100,
    r: 0.05,
    sigma: 0.2,
    T: 1.0,
    steps: 100,
    N: 10000,
    type: "call"
  });

  const [result, setResult] = useState<any>(null);
  const [surfaceData, setSurfaceData] = useState<any>(null); // Placeholder for surface data
  const [loading, setLoading] = useState(false);

  const calculate = async () => {
    setLoading(true);
    try {
      const response = await fetch('/api/price', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        },
        body: JSON.stringify(params),
      });
      const data = await response.json();
      setResult(data);

      // Simulate surface generation for now (real app would fetch 2D array from backend)
      // This is a placeholder to demonstrate the UI capability
      const x_range = Array.from({length: 20}, (_, i) => params.S0 * (0.5 + i * 0.05));
      const y_range = Array.from({length: 20}, (_, i) => params.sigma * (0.5 + i * 0.05));
      const z_data = y_range.map(vol => 
          x_range.map(spot => Math.max(spot - params.K, 0) * Math.exp(-params.r * params.T)) // Simply intrinsic for visual
      );
      setSurfaceData({ x: x_range, y: y_range, z: z_data });

    } catch (error) {
      console.error("Error calculating price:", error);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="min-h-screen bg-slate-950 p-6 md:p-12">
      <div className="max-w-7xl mx-auto space-y-8">
        
        {/* Header */}
        <header className="flex flex-col md:flex-row md:items-center justify-between gap-4 border-b border-slate-800 pb-6">
          <div>
            <h1 className="text-3xl font-bold bg-clip-text text-transparent bg-gradient-to-r from-blue-400 to-indigo-400">
              Asian Option Pricer V2
            </h1>
            <p className="text-slate-400 mt-1">High-performance Monte Carlo Engine</p>
          </div>
          <button 
            onClick={calculate}
            disabled={loading}
            className="flex items-center gap-2 bg-brand-primary hover:bg-blue-600 text-white px-6 py-3 rounded-xl font-semibold shadow-lg shadow-blue-500/20 transition-all disabled:opacity-50"
          >
            {loading ? <div className="animate-spin rounded-full h-5 w-5 border-2 border-white/20 border-t-white" /> : <Play className="h-5 w-5" />}
            Calculate Price
          </button>
        </header>

        <div className="grid grid-cols-1 lg:grid-cols-12 gap-8">
          
          {/* Left Column: Inputs */}
          <div className="lg:col-span-4 space-y-6">
            <Card title="Parameters">
              <div className="grid grid-cols-2 gap-4">
                <InputParam label="Spot Price (S0)" value={params.S0} onChange={(v) => setParams({...params, S0: parseFloat(v)})} />
                <InputParam label="Strike (K)" value={params.K} onChange={(v) => setParams({...params, K: parseFloat(v)})} />
                <InputParam label="Risk-free Rate (r)" value={params.r} onChange={(v) => setParams({...params, r: parseFloat(v)})} step="0.001" />
                <InputParam label="Volatility (σ)" value={params.sigma} onChange={(v) => setParams({...params, sigma: parseFloat(v)})} step="0.01" />
                <InputParam label="Maturity (T)" value={params.T} onChange={(v) => setParams({...params, T: parseFloat(v)})} />
                <InputParam label="Steps" value={params.steps} onChange={(v) => setParams({...params, steps: parseInt(v)})} type="number" />
                <InputParam label="Simulations (N)" value={params.N} onChange={(v) => setParams({...params, N: parseInt(v)})} type="number" step="1000" />
                
                <div className="flex flex-col gap-1.5">
                  <label className="text-xs font-medium text-slate-400 uppercase tracking-wider">Option Type</label>
                  <select 
                    value={params.type}
                    onChange={(e) => setParams({...params, type: e.target.value})}
                    className="bg-slate-950 border border-slate-800 text-slate-100 rounded-lg px-3 py-2 text-sm focus:ring-2 focus:ring-brand-primary outline-none"
                  >
                    <option value="call">Call</option>
                    <option value="put">Put</option>
                  </select>
                </div>
              </div>
            </Card>
          </div>

          {/* Right Column: Results & Visualization */}
          <div className="lg:col-span-8 space-y-6">
            <div className="grid grid-cols-1 md:grid-cols-2 gap-6">
                 {/* Price Card */}
                <Card className="flex flex-col justify-center items-center py-8 relative overflow-hidden group">
                   <div className="absolute inset-0 bg-gradient-to-br from-blue-500/10 to-transparent opacity-0 group-hover:opacity-100 transition-opacity" />
                   <span className="text-slate-400 uppercase tracking-widest text-xs font-medium mb-2">Estimated Option Price</span>
                   <div className="text-5xl font-bold text-white tracking-tight">
                        {result ? `$${ result.price.toFixed(4) } ` : <span className="text-slate-700">---</span>}
                   </div>
                </Card>
                 
                 {/* Greeks Summary Card (Simplification or extra metric) */}
                 <Card className="flex flex-col justify-center p-6">
                    <span className="text-slate-400 uppercase tracking-widest text-xs font-medium mb-4">Model Status</span>
                    <div className="flex items-center gap-2">
                         <div className={`h - 2 w - 2 rounded - full ${ loading ? 'bg-yellow-500 animate-pulse' : 'bg-green-500' } `} />
                         <span className="text-sm text-slate-300">{loading ? 'Calculating...' : 'Ready'}</span>
                    </div>
                    <div className="mt-4 text-xs text-slate-500">
                        Method: Monte Carlo<br/>
                        Model: Black-Scholes / Heston
                    </div>
                 </Card>
            </div>

            {/* Greeks Panel */}
            {result && (
              <Card title="Greeks Sensitivity">
                <GreeksDisplay 
                   delta={result.delta} 
                   gamma={result.gamma} 
                   vega={result.vega} 
                   theta={result.theta} 
                   rho={result.rho} 
                />
              </Card>
            )}

            {/* Volatility Surface */}
            <VolatilitySurface data={surfaceData} />

          </div>
        </div>
      </div>
    </div>
  );
}

export default App;
