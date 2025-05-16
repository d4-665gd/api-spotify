'use client';
import { useCarrito } from '@/app/context/CarritoContext';
import { useParams } from 'next/navigation';
import React,{ useEffect, useState } from 'react';
import toast from 'react-hot-toast';
import {BarraLateral} from '@/app/components/Menu';

type Producto = {
  id: string;
  nombre: string;
  artista: string;
};

const Canciones: Producto[] = [
  { id: "1", nombre: "Blinding Lights", artista: "The Weeknd" },
    { id: "2", nombre: "Levitating", artista: "Dua Lipa" },
    { id: "3", nombre: "Watermelon Sugar", artista: "Harry Styles" },
    { id: "4", nombre: "Peaches", artista: "Justin Bieber" },
    { id: "5", nombre: "Save Your Tears", artista: "The Weeknd" },
    { id: "6", nombre: "Good 4 U", artista: "Olivia Rodrigo" },
    { id: "7", nombre: "MONTERO", artista: "Lil Nas X" },
    { id: "8", nombre: "Kiss Me More", artista: "Doja Cat" },
    { id: "9", nombre: "Stay", artista: "The Kid LAROI & Justin Bieber" },
    { id: "10", nombre: "Drivers License", artista: "Olivia Rodrigo" },
];

export default function DetalleProducto() {
  const params = useParams();
  const [mensajeAgregado,setmensajeAgregado] = useState(false);
  const [Mensaje,setMensaje] = useState('');
  const id = Array.isArray(params.id) ? params.id[0] : params.id;
  const [producto, setProducto] = useState<Producto | null>(null);
  const { agregarAlCarrito } = useCarrito();

  useEffect(() => {
    if (!id) return;
    
    const productoEncontrado = Canciones.find((p) => p.id === id);
    setProducto(productoEncontrado || null);
  }, [id]);

  useEffect(() => {
    if (Mensaje) {
      const timer = setTimeout(() => {
        setmensajeAgregado(false);
        setMensaje(''); // Limpia el mensaje
      }, 2000); // 2000 milisegundos = 2 segundos
      return () => clearTimeout(timer); // Limpia el timer si el componente se desmonta o el estado cambia
    }
  }, [mensajeAgregado]); 

  const handleAgregar = () => {
    if (producto) {
      agregarAlCarrito(producto); // Llama a la función del contexto para agregar al carrito
      toast.success(`"${producto.nombre}" agregado al carrito!`, { // Muestra el toast de éxito
        duration: 2000, // Duración de 2 segundos
      });
    } else {
      // Manejar el caso en que el producto no se encuentre
      toast.error('Producto no encontrado.');
    }
  };

  if (!producto) return <p>Producto no encontrado.</p>;

  return (



    <div className="flex min-v-screen"> {/* Flex layout horizontal */}
          
                 
   <div>
      <h1><b>{producto.nombre}              </b></h1>
      </div>
      
          <div>
          <h2>   Artista: {producto.artista}  </h2>
          </div>
          
      
      <div className='text-center'>
      <button
  onClick={handleAgregar}
  className='boton-spotify' >
  Agregar al carrito
</button>

     
</div>

    </div>
  );
};


