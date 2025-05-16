# EXplicacion codigo
parse_command() se encraga de dividir las funciones de un comando por por el simbolo <b> |</b> mediante la funcion *strtok(input,"|")* para guardar cada pedazo entre pipes como un comando que los guarda en el arreglo **commands** .
parse_args() toma cada comando para separarlo por palabra  (hasta llegar a NULL) mediante la primera linea de la funcion para luego ser ejecutado por *execvp()* meiante un ciclo y guarfdar cada palabra en el arreglo args hasta hayar NULL para poner NULL en la posicion i para cerrar la lisat.
commands es un arrelo de punteros a char que guarda cada uno de las instrucciones de un comando mientras line es un arreglo que guarda el comando completo y pipe_fd es es una tuberia matriz con su extremo de lectura y escritura cuyo numero de tuberias es el maximo de instr. -1 .
 fflush(stdout); - limpia el buffer de salida para imprimir lo que esta en el printf en la salida estandar.
 if (!fgets(line, sizeof(line), stdin)) break; - se encarga d leer la linea de comando que se guarda en *line* con un maximo de caracteres a leer del tamaño del comando por la entrada estandar (teclado) y terminar la ejecucion si no hay nada.
 line[strcspn(line, "\n")] = 0;
if (strcmp(line, "") == 0) continue;
if (strcmp(line, "exit") == 0) break; devuelve la primera posicion en el primer salto de linea.
for (int i = 0; i < num_cmds - 1; ++i)
            pipe(pipe_fd[i]); 
crean las tuberias repecto al num de comandos menos 1.

for (int i = 0; i < num_cmds; ++i) {
            pid_t pid = fork();
SE crea un proceso hijo por cada comando escrito.
if (pid == 0) {
    Redirección de entrada 
    if (i > 0) {
dup2(pipe_fd[i - 1][0], STDIN_FILENO);
                }
verifica si se encuentra dentro del proceso hijo para ejecutar uno de los comandos llegando al primer pipe conectando su entrada(STTDIN) al extremo de lectura del tubo.
if (i < num_cmds - 1) {
    dup2(pipe_fd[i][1], STDOUT_FILENO);
                }
pasa al estado de escritura de cada comando.
despues cierran el roceso de cada pipe.
prosigue la ejecucion de cada comando por separado para execvp().
s cierran todos los extremos del pipe y espera a todos los hijos para acabar.
for (int i = 0; i < num_cmds; ++i)
            wait(NULL);
hace que el proceso principal (el padre) espere a que todos los procesos hijos terminen antes de finalizar. Así se asegura de no cerrar el programa hasta que todos los comandos hayan terminado su trabajo..