'use client';
import Link from 'next/link';
import { useState } from 'react';
import Image from 'next/image';
import {IoLogoReact} from 'react-icons/io5';
import {FaMusic,FaShoppingCart} from 'react-icons/fa';
import {MdLibraryMusic} from 'react-icons/md';
import { BarraLateralElem } from './BarraLateralElem';
import React from 'react';
//yarn add react-icons
 
interface BarraLateralProps {
    setvistaActiva : (vista: string) =>void;
}

const MenuElementos = [
    {
       id: "menu/productos",
       icon: <FaMusic size={40} />,
       title : "Productos",
       subtitle: "Top 10 canciones"
    },
    {
        id: "menu/producto",
        icon: <MdLibraryMusic size={40} />,
        title : "Producto",
        subtitle: "Descripción del producto"
     },
     {
        id: "menu/carrito",
        icon: <FaShoppingCart size={40} />,
        title : "Carrito",
        subtitle: "Almacena tu compra aqui"
     }
];

export const BarraLateral = ({setvistaActiva }:BarraLateralProps) => {
    return (
    <div id="menu" className="bg-gray-900 min-h-screen z-10 text-slate-300 w-64 left-0 overflow-y-scroll">
        <div id="logo" className="my-4 px-6">
            <h1 className="flex items-center text-lg md:text-2xl font-bold text-white">
                <IoLogoReact className='mr-2' />
                <span> Tienda </span> <span className='text-blue-500'> Spotify</span>
            </h1>
            <p className="text-slate-500 text-sm"> Tu catalogo musical</p>
        </div>
        <div id="profile" className="px-6 py-10">
            <p className="text-slate-500">Bienvenido,</p>
            <a href="#" className="inline-flex space-x-2 items-center">
                <Image className="rounded-full w-8 h-8" 
                src="https://images.unsplash.com/photo-1517686748843-bb360cfc62b3"
                alt="User avatar"
                width={50}
                height={50}/>
                <span className="text-sm md:text-base font-bold">Usuario Musical</span>
            </a>
        </div>

                <div id="nav" className="w-full px-6">
                    {MenuElementos.map( item => (
                        <Link  href={`/${item.id}`} key={item.id}
                        className="flex items-center space-x-3 p-3 hover:bg-white/10 rounded transition"
                             >
                             
                            <div className="text-white">
                                  {item.icon}
                            </div>
                            <div>
                                <h2 className="text-slate-300 font-bold"> {item.title}</h2>
                               <p className="text-sm text-slate-500">{item.subtitle}</p>
                            </div>
                            
                        </Link >
                    )) } 
                </div>
          </div> 
    ); 
};

//export default BarraLateral;