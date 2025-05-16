type Producto = {
    id:string;
    nombre:string;
    artista:string;
};

interface Props{
    producto: Producto;
    Agregar: (producto: Producto) => void; 
}

const ProductoItem = ({producto, Agregar}: Props) =>{
   return (
       <div style= {{border: '1px solid gray', 
       padding: '0.5rem', marginBottom: '0.5rem'}}>
       <p> {producto.nombre} - {producto.artista} </p>
       <button onClick={() => Agregar(producto)}> Agregar </button>
       </div>
   );
};

export default ProductoItem;