"use client";
import ProductoItem from "../components/ProductoItem";
import Carrito from "../components/Carrito";
import { ProductosLista } from "../components/ProductoLista";
import { ProductoDetalle } from "../components/ProductoDetalle";
import {BarraLateral} from '../components/Menu';

import { useEffect, useState } from "react"; 

const Pag_Principal =() =>{

      
const [vistaActiva, setvistaActiva] = useState("productos");
const [productoSeleccionado, setProductoSeleccionado] = useState(null);


    return (
      
        <div className="flex">
         <BarraLateral /> 
        <div className="flex-1 p-4">
              {vistaActiva === "productos" && (<ProductosLista
                  onSeleccionarProducto={(producto) => {
                     setProductoSeleccionado(producto);
                     setvistaActiva("producto");
                  }}
                       />
                      )}
               {vistaActiva === "producto" && (<ProductoDetalle producto={productoSeleccionado}/>
              )}
             {vistaActiva === "carrito" && <Carrito carrito={carrito} ModifCantidad={ModifCantidad} Total={Total}/>}
        </div>
        </div>
                );
                

            
        };

        export default Pag_Principal;