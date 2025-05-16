import React from 'react';


type Producto = {
     id: string;
     nombre: string;
     artista: string;
};

interface Props  {
    onSeleccionarProducto: ( producto: Producto) => void;
}

const Canciones = [
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

 export const ProductosLista = ({onSeleccionarProducto}:Props) => {
                   return (
                   < div className="h-[90vh] overflow-y-auto p-4">
                    <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 gap-4">
                       {Canciones.map( cancion => (
                          <div 
                          key={cancion.id} 
                          className=" bg-gray-100 p-4 rounded shadow cursor-pointer hover:bg-gray-200 transition"
                                onClick={()=> onSeleccionarProducto(cancion)}>
                                    <h3 className="font-semibold"> {cancion.nombre}</h3>
                                   <p className="text-sm text-gray-600">{cancion.artista}</p>
                             </div>  
                   ))}
                   </div>
                   </div>
                   );
 };