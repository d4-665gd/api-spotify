"use client"

import React from "react";

type Producto = {
    id: string;
    nombre: string;
    artista: string;
    cantidad: number;
}

type Props = {
    carrito: Producto[];
    ModifCantidad : (id:string, cantidad: number) => void;
    Total: () => number;
}

const Carrito: React.FC<Props> = ({carrito, ModifCantidad, Total}) => {
    return (
          <div style={{marginTop: "2rem", border: "1px solid #ccc", padding: "1rem"}}> 
              <h3> Carrito de compras </h3>
              {
                carrito.length === 0 ? (
                    <p> Tu carrito esta vacio</p>
                ) : (
                    carrito.map((item) => (
                    <div key={item.id} style={{marginBottom:"1rem" }}> 
                        <p>
                            {item.nombre} - {item.artista}
                        </p>

                            <div>
                        <button onClick={()=> ModifCantidad(item.id, item.cantidad - 1)}>
                             -
                        </button>
                        <span style={{margin:"0 0.5rem"}}>{item.cantidad}</span>
                        <button onClick={()=> ModifCantidad(item.id, item.cantidad - 1)}>
                             +
                        </button>      
                            </div>
                     </div>
                    ))
                )
              }
                <h4> Total: ${Total().toFixed(2)}</h4>
          </div>
    ); 
};
export default Carrito;