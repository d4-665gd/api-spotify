'use client';

import React from 'react';

import { useCarrito } from '@/app/context/CarritoContext';
import { BarraLateral } from '@/app/components/Menu';

const ContenidoPaginaCarrito = () => {
  const { carrito, modificarCantidad } = useCarrito();

  const Total = () => {
    return carrito.reduce((acc, item) => acc + item.cantidad * 10, 0);
  };

  return (
    <div style={{ flexGrow: 1, padding: '1rem' }}>
      <h3><b>Carrito de compras
        
        
        </b></h3>
      {carrito.length === 0 ? (
        <p>Tu carrito está vacío</p>
      ) : (
        carrito.map((item) => (
          <div key={item.id} style={{ marginBottom: '1rem' }}>
            <p>
              {item.nombre} - {item.artista}
            </p>
            <div>
              <button
                onClick={() => modificarCantidad(item.id, item.cantidad - 1)}
                disabled={item.cantidad <= 0}
              >
                -
              </button>
              <span style={{ margin: '0 0.5rem' }}>{item.cantidad}</span>
              <button onClick={() => modificarCantidad(item.id, item.cantidad + 1)}>
                +
              </button>
            </div>
          </div>
        ))
      )}
      <h4>Total: ${Total().toFixed(2)}</h4>
    </div>
  );
};

export default ContenidoPaginaCarrito;
