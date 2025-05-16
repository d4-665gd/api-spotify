//import Link  from 'next/link';
import {ReactNode} from 'react';


interface Props  {
    id: string;
    icon: ReactNode;
    title: string;
    subtitle: string;
}

export const BarraLateralElem = ({id,icon,title,subtitle, onSelect}: any) => (
      
                    
              
                <div
                 className="curosr-pointer hover:bg-white/5 p-2
                 onClick={() => onSelect(id)}">

                  <div className="flex items-center space-x-2">{icon}
                        <div>
                           <h2>{title}</h2>
                        <p className="text-sm text-gray-400">{subtitle}</p>
                        </div>
                    </div>
                  
                 </div>
              
     );