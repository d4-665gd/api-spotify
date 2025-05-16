'use client';

import React from 'react';
import dynamic from 'next/dynamic';
import {BarraLateral} from '../../components/Menu';

const ContenidoPaginaCarrito = dynamic(() => import('./ContenidoPaginaCarrito'), {
  ssr: false,
});

const PaginaCarrito = () => {
  
  return <ContenidoPaginaCarrito />;
};

export default PaginaCarrito;
