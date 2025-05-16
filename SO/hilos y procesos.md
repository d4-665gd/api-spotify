# Procesos e Hilos
## <font color="#1ecb3c"> **Proceso** </font>: <sub>`entidad ejecutable con identificador para referencia del sistema`</sub>  
## <p> <li> Son independientes
## <p> <li> Comunicables a travez de un *mecanismo*

## <font color=" #d13323 "> **Hilo** </font>: <sub>`unidad de ejecución de un proceso`</sub> 
### <p> <font color="  #d7e906  "> Introducción a procesos </font>
### <p> Un proceso puede estar `en el procesador` *ejecutandose* _   (ejecución) o `fuera de el` (no ejecución) *en espera de hacerlo*. El sistema debe tener **su estado actual posición de memoria** y los demas procesos esperar en una **estructura de cola** para su turno.
### - *Posibles problemas*.
### <li> Procesos de **no ejecución** estan en la cola de ejecución.
### <li> Procesos bloqueados por una operacion de E/S.
### <p> Por ello se crea el `El diagrama de estados de procesos` (Fig 1.) donde `1.- Running a Blocked` ocurre cuando hay un proceso que no puede continuar, `2.- Running a Ready` ocurre cuando el programador decide terminar un proceso para continuar con otro proceso, `3.- Ready a Running ` ocurre cuando se vuelve a ejecutar un primer proceso luego de que los demas se hayan completado y `4.- Blocked a Ready` ocurre cuando se recibe la repuesta que un proceso estaba esperando.
  <img src="m.png"  style="width:538px;height:159px;"> 

### <font color="green"> *Notas :*</font> <sub> 
<li> swapper es el proceso 0.
<li> El estado zombi es el estado final de un proceso.</sub>

### <p> <font color="  #d7e906  "> Control de procesos </font>.
### <p> Un sistema debe **crear**, **manejar** y **eliminar** un proceso. Crearlo implica:

### <li> Asignar identificador.
### <li> Insertarlo en la lista de procesos.
### <li> Determinar prioridad inicial.
### <li> Crear bloque de control.
### <li> Asignarle recursos.
### Cuando de añade a la lista: <li> se constuyen las estructuras de datos que se utilizan ara administrar el proceso. <li> asignar el espacio de direcciones a utilizar.
### <font color="green"> *Notas :*</font> <sub> Un proceso genera otro proceso (Proceso padre genera proceso hijo).</sub>
### <p> <font color="  #d7e906  "> Sistemas de llamado para crear procesos </font>.
### Los procesos pueden ser creados de forma directa (*creando una aplicación*) o indirectamente *por una llamada fork*.