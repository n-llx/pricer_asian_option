import React from 'react';
import { clsx, type ClassValue } from 'clsx';
import { twMerge } from 'tailwind-merge';

function cn(...inputs: ClassValue[]) {
    return twMerge(clsx(inputs));
}

interface CardProps extends React.HTMLAttributes<HTMLDivElement> {
    title?: string;
}

export function Card({ title, children, className, ...props }: CardProps) {
    return (
        <div className={cn("bg-slate-900 border border-slate-800 rounded-xl p-6 shadow-xl", className)} {...props}>
            {title && <h3 className="text-lg font-semibold text-slate-100 mb-4">{title}</h3>}
            {children}
        </div>
    );
}
