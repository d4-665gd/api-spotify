// src/app/tienda-spotify/src/app/menu/layout.tsx
import React from 'react';
import { BarraLateral } from '../components/Menu'; // Asegúrate de que la ruta de importación sea correcta

const MenuLayout = ({ children }: { children: React.ReactNode }) => {
  return (
    <div className="flex"> {/* O la clase CSS que uses para tu layout */}
      <BarraLateral />
      <main className="flex-grow"> {/* O la clase CSS para el contenido principal */}
        {children}
        
        
      </main>
    </div>
  );
};

export default MenuLayout;
