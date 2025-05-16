import { ReactNode } from "react";

interface Props{
    children : ReactNode;
}

const MenuBarra = ({children}: Props) => {
    return (
        <div style = {{display: 'flex', height: '100vh'}}>
        <aside style = {{  width: '200px', background: '#f3f3f3'}}>
            <ul>
               <li> Productos </li> 
               <li> Carrito</li> 
            </ul>
            </aside>
            
            <main style= {{flex:1, padding: '1rem'}}>
                {children}
            </main>
            </div>
            );
            };

export default MenuBarra;            