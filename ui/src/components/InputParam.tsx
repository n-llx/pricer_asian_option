import React from 'react';

interface InputParamProps {
    label: string;
    value: number | string;
    onChange: (val: string) => void;
    step?: string;
    min?: string;
    max?: string;
    type?: string;
}

export function InputParam({ label, value, onChange, step = "0.01", min, max, type = "number" }: InputParamProps) {
    return (
        <div className="flex flex-col gap-1.5">
            <label className="text-xs font-medium text-slate-400 uppercase tracking-wider">{label}</label>
            <input
                type={type}
                value={value}
                onChange={(e) => onChange(e.target.value)}
                step={step}
                min={min}
                max={max}
                className="bg-slate-950 border border-slate-800 text-slate-100 rounded-lg px-3 py-2 text-sm focus:ring-2 focus:ring-brand-primary focus:border-transparent outline-none transition-all"
            />
        </div>
    );
}
