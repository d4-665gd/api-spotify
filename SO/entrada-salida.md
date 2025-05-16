# E/S
El sistema opetativo y los controladores del dispositivo.
Empresas requieran que lo laborado sea un modulo kernel.
modulo de kernel: es un fragmento de cofigo que extiende las funcionalidades de este y cargar dinamicamente sin reiniciar.
en e/s se habla del bloqueo mutuo: SO concede temporalmente acceso exlcusivo a reursos por un solo proceso a la vez (tambien es interbloqueo). un porceso A espera de un mismo conjunto de procesos al proceso F (hay exporpiables y no expropiables (bloqueo mutuo) (arrebatar sin efectos adversos y no)).

La secuecnia de sucesos es :

solicitar recurso
usarlo
liberar recurso.
DEben cumplirse 4 condiciones (Coffman 1971).
1. exclusion mutua - cada recurso asugnado a un proceso o esta disponibel.
2. retener y esperar - los procesos que tienen recursos puden solicitar nuevos.
3- no expropiacion- los recursos deben liberarse explicitamente.
5 espera circular -una cadena circular de m procesos cada uno esperando al sguiente.
arco recurso-proceso recurso asignado a un proceso.
arco proceso - recurso proceso bloqueado
Algoritmo del avestruz - no hacer nada para no generar interbloqueo
no se puede saber el orden de ejecucion de procesos