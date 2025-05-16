
type Producto = {
    id: string;
    nombre: string;
    artista: string;
};

type Props = {
      producto: Producto | null;
};

export const ProductoDetalle = ({producto}: Props) => {
     if(!producto) return <p>No dr ha seleccionado ningun producto.</p>;

     return (
           <div className="p-4 bg-white rounded shadow">
              <h1 className="text-2xl font-bold mb-2">{producto.nombre}</h1>
              <p className="text-gray-700">Artista: {producto.artista}</p>
              <p className="mt-4 text-sm text-gray-500">Id: {producto.id}</p>
           </div>
     );
};