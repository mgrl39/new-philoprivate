# Explicacion del proyecto Phiossopheerrs
(EL CODIGO VA A IR CAMBIANDO. ESTA DOCU CAPAZ ES PASDA PERO EES PARA ENTENDER LA LOGICAA QUE HABIA)
Este proyecto es una simulacion del problema de los filosofs comensales usando hilos (pthread) y mutex para sincronizacion.

## Estructrua 
```c
struct	s_table {
	int	num_philos;	// Numero de filosofos
	int	time_to_die;	// Tiempo maximo sin comer (ms)
	int	time_to_eat;	// Tiempo comiendo (ms)
	int	time_to_sleep;	// Tiempo durmiendo (ms)
	int	num_meals;	// Comidas requeridas (-1 = infinito)
	int	someone_died;	// Bandera de muerte 
	long	start_time;	// Tiempo de inicio
	pthread_mutex_t	*forks;	// Mutex para tenedores
	pthread_mutex_t	write_lock; // Mutex para salida
	pthread_mutex_t	meal_lock; // Mutex para acceso a comidas
	pthread_mutex_t	death_lock; // Mutex para acceso a muerte
	t_philo	*philos;
}	t_table;

struct	s_philo {
	int	id; // Id del filosofo
	int	meals_eaten;	// Comidas consumidas
	long	last_meal_time;	// Ultimo tiempo de comida
	pthread_mutex_t	*forks[2] // Tenedores (Izquierdo y derecho)
	pthread_t	thread;	// Hilo del filosofo
}	t_table	*table;

```

## Flujo principal
1. Inicializacion (`init.c`):
- Valida argumentos de entrada.
- Crea mutex para tenedores y locks de control
- Asigna tenedores a cada filosofo (izquierrdo y derecho)
- Caso especial: 1 filosofo (solo tiene 1 tenedor)

2. Simulacion (`main.c`):
```c
int	main(void)
{
	validar_argumentos();
	init_table(); // Inicializa la mesa y ls filosofos
	start_simulation(); // Lanza hilos
	monitor_simulation(); // Supervisa estado
	clean_table(); // Libera recursos
}
```

3. Rutina de filosofos (`routine.c`):
```c
void	*philo_loop() {
	while (!muerte && !comidas_completas) {
		take_forks(); // Toma tenedores (evitando deadlock)
		eat();	// Actuliza ultima comidaa
		sleep_and_think();
	}
}
```
Estrategia anti-deadlock:
- Filosofos pares: toman tenedor DERECHO primero
- Filosofos impares: toman tenedor IZQUIERDO primero

4. Monitorizacion (`monitor.c`)
- Verifica cada X ms:
	- Si algun filosofo supera `time_to_die` sin comer
	- Si todos completaron las comidas requeridas
- Usa mutex paara accceder a datos compartidos

## Mecanismos clave
1. Un solo filosofo:
- Solo tiene un tenedor --> No puede comer --> Muere
```c
if (table->num_philos == 1) philo->forks[RIGHT] = NULL; // Sin tenedor derecho
```
2. Comidas infinitas
Si `num_meals = -1`, lso filosofos comen indefinidamente
3. Finalizacion:
- Por muerte de un filosofo
- Por completar todas las comidas

## Detalles de la implementacion:
1. Inicializacion de mutex (init_mutexes):
- Crea un mutex por tenedor
- Inicializa locks para escritura/comidas/muerte
2. Anti-starvation:
- Filosofos pares esperan 10ms antes de empezar
```
if (philo->id % 2 == 0) usleep(10000);
```
3. monitor eficiente:
- Verificacion pr lotes, no continua:
- Sleep de 1ms entre cheuqeos para reducir CPU

## Por Que funciona
1. Deadlock Prevention:
- Orden inverso de tenedores para pares/impares
- Solucion clasica del problema

2. Starvaation prevention:
- Retardo inicial paara filosofsoo pares
- Monitizacion periodica

3. Thread Safety
- Todos los datos compartidos protegidos con mutex
 Operaciones atomicas en secciones criticas
