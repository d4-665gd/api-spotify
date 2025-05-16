'use client';

import { useRouter } from "next/navigation";
import React from "react";
import { BarraLateral } from '@/app/components/Menu';

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

export default function ProductosPage() {
  const router = useRouter();

  return (
    <div className="flex min-h-screen"> {/* Flex layout horizontal */}
      

      <div className="flex-1 h-[90vh] overflow-y-auto p-4 bg-white">
        <h1 className="text-2xl font-bold mb-4">Lista de Canciones</h1>
        <div className="grid grid-cols-1 sm:grid-cols-2 md:grid-cols-3 gap-4">
          {Canciones.map((cancion) => (
            <div
              key={cancion.id}
              onClick={() => router.push(`producto/${cancion.id}`)}
              className="bg-gray-100 p-4 rounded shadow hover:bg-gray-200 cursor-pointer transition"
            >
              <h3 className="font-semibold">{cancion.nombre}</h3>
              <p className="text-sm text-gray-600">{cancion.artista}</p>
            </div>
          ))}
        </div>
      </div>
    </div>
  );
}
