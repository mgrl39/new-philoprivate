# Conceptos clave de Concurrencia
## Problemas Comunes
1. Condicion de Carrera
- Dos hilos acceden a un recurso compartido sin sincornizacion.
- SOLUCION: Mutex para acceso exclusivo.

2. Deadlock:
- Hilo 1 tiene recurso A y necesita B
- Hilo 2 tiene recurso B y necesita A
- Solucion: Orden consistente en adquisicion de recursos.

3. Inanicion:
- Algunos hilos nunca obtienen recursos
- Solucion: Estrategias de prioridad (en este caso, orden de tenedores)

## Patrones usados en el proyecto
1. Mutex como semaforo binario:
```c
pthread_mutex_lock(&recurso);
// Zona critica
pthread_mutex_unlock(&recurso);
```
2. Bandera atomica con Mutex:
```c
pthread_mutex_lock(&lock);
flag = valor;
pthread_mutex_unlock(&lock);
```
3. Retraso inicial para Equilibrio:
```c
if (philo->id % 2 == 0) usleep(10000);
``

