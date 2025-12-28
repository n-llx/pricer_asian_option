import React from 'react';
import { TrendingUp, Activity, BarChart2, Clock, Zap } from 'lucide-react';

interface GreeksProps {
    delta: number;
    gamma: number;
    vega: number;
    theta: number;
    rho: number;
}

export function GreeksDisplay({ delta, gamma, vega, theta, rho }: GreeksProps) {
    const items = [
        { label: "Delta", value: delta, icon: TrendingUp, color: "text-blue-400" },
        { label: "Gamma", value: gamma, icon: Activity, color: "text-purple-400" },
        { label: "Vega", value: vega, icon: Zap, color: "text-yellow-400" },
        { label: "Theta", value: theta, icon: Clock, color: "text-red-400" },
        { label: "Rho", value: rho, icon: BarChart2, color: "text-green-400" },
    ];

    return (
        <div className="grid grid-cols-2 lg:grid-cols-5 gap-4">
            {items.map((item) => (
                <div key={item.label} className="bg-slate-950/50 rounded-lg p-4 border border-slate-800/50 flex flex-col items-center justify-center text-center hover:bg-slate-800/50 transition-colors">
                    <item.icon className={`h-5 w-5 mb-2 ${item.color}`} />
                    <span className="text-xs text-slate-500 font-medium uppercase">{item.label}</span>
                    <span className="text-lg font-bold text-slate-100 mt-1">{item.value.toFixed(4)}</span>
                </div>
            ))}
        </div>
    );
}
