import {useState} from 'react';
import {BarraLateral} from '@/app/components/Menu';
import { ProductosLista } from './ProductoLista';
import { ProductoDetalle } from './ProductoDetalle';
import {Carrito} from '@/app/components/Carrito';

export default function Menu() {
    const [vistaActiva, setvistaActiva] = useState("productos");

    return (
               <div className="flex min-h-screen">
                <BarraLateral setvistaActiva={setvistaActiva} />
                <main className="flex-1 p-4 bg-white">
                    {vistaActiva === "productos" && <ProductosLista onSeleccionarProducto={() => setvistaActiva("producto")}/>}
                    {vistaActiva === "producto" && < ProductoDetalle/>}
                    {vistaActiva === "carrito" && <Carrito/>}
                    </main>
               </div>
    );
}