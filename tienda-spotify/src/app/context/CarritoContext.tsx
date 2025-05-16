'use client';

import React, { createContext, useContext, useState, ReactNode } from 'react';

type Producto = {
  id: string;
  nombre: string;
  artista: string;
  cantidad: number;
};

type CarritoContextType = {
  carrito: Producto[];
  agregarAlCarrito: (producto: Omit<Producto, 'cantidad'>) => void;
  modificarCantidad: (id: string, cantidad: number) => void;
};

const CarritoContext = createContext<CarritoContextType | undefined>(undefined);

export const useCarrito = () => {
  const context = useContext(CarritoContext);
  if (!context) {
    throw new Error('useCarrito debe usarse dentro de CarritoProvider');
  }
  return context;
};

export const CarritoProvider = ({ children }: { children: ReactNode }) => {
  const [carrito, setCarrito] = useState<Producto[]>([]);

  const agregarAlCarrito = (producto: Omit<Producto, 'cantidad'>) => {
    setCarrito(prev => {
      const existe = prev.find(p => p.id === producto.id);
      if (existe) {
        return prev.map(p =>
          p.id === producto.id
            ? { ...p, cantidad: p.cantidad + 1 }
            : p
        );
      } else {
        return [...prev, { ...producto, cantidad: 1 }];
      }
    });
  };

  const modificarCantidad = (id: string, cantidad: number) => {
    setCarrito(prev =>
      prev.map(p =>
        p.id === id
          ? { ...p, cantidad: Math.max(0, Math.min(20, cantidad)) }
          : p
      )
    );
  };

  return (
    <CarritoContext.Provider value={{ carrito, agregarAlCarrito, modificarCantidad }}>
      {children}
    </CarritoContext.Provider>
  );
};