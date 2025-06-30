# Descripcion general

-  Uno o mas filosofos se sientan en una mesa redonda.
- En el centro de la mesaa se encuentra un gran bol de espaguetis

- Los filosofos solo pueeden comer, pensar o dormir
Mientras estan comiendo, no pueden pensar ni dormir;
Mientras estan ppensando, no pueden dormir ni comer;;
Y, por supuesto, mientras estsan durmiendo, no pueeden comer ni peensar.


- Tambien haay tenedores en laa mesa,a tantos tenedores como filosofos

- Porquee coger y come espaguetis con un solo tenedor puede ser incomdo, los filosofso
deben tomar el tenedor de la derecha y el de la izquierda, uno en cada mano.

- Cuando un filosofoo temrmine de comer, dejara los tenedores en la mesa e inmediatamente
empezara a dormir. Una vez se despierte, empezara a pensar neuvamente.
La simulacion se detendra cuando unfilosofo muere por inanicion.

- Todos los filsofos necesitan comer y nunca deben morir de hambre

- Los filosofso no hablan entre ellos

- Los filosofos no saben si otro filosofo va a morir

- No deberia haacer falta decir que todos deben evitar morir

## Instrucciones generales

Deberas escribir un programa para la parte obligatoria y otro paara la parte bonus (Solo si decides hacer la parte bonus). Ambas tienen que cumplir con las siguiete reglas:

- Las variables globales estan prohibidas.

- Tu(s) programa(s) debe(n) aceptar los siguientes argumentos:

number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher__must_eat]


- number_of_philosophers: es el numero de filosofos, pero tambien el numero de tenedores
- time_to_die (en milisegundos): si un filsofo no empiezaa a comer en time_to_die milisegundos desde el comeinzo de su ultima comida ao desde el rpicinipio de la simulacion, este morira
- time_to_eat (en milisegundos): es el timepo que tiene un filosof para comer. Durante ese timepom tendra los tenedores ocupados
- time_to_sleep (en milisegundos) es el tiempo que tiene un flosofo par adormir.
- number_of_times_each_philosopher__must_eat (argumento opcional): si todos lso filosofso comoeen al menos number_of_times_each_philosopher__must_eat veces, la simulacion se detendra. Si no se especifica, al simualcion se detiene con la muerte de un filsofo.

Cada filosofo tendra asignado un numero de 1 al number_of_philosophers

El filosofo numeror 1 se sentra al lado del filosofo numero number_of_philosophers. Cualquier otro numero N se sentaran entre el filosof numero N - 1 y el fiosofo numero N + 1

Los logs de tu programa:
- Cuaqluier cambio de estado de un fiossofo debe tener el siguieente formato:
	 - timestamp_in_ms X has taken a fork
	 - timestamp_in_ms X is eating
	 - timestamp_in_ms X is sleeping
	 - timestamp_in_ms X is thinking
	 - timestamp_in_ms X died

Reemplaza timestamp_in_ms con la marca de tiempo actual en milisegundos y X con el nmero de filosofo.

- El estado impreso no debe estar rooto o alterado por el estado de otros filosofos.
- no puedes ener mas de 10ms entre la muerte de un filosofo y el momento en el que imprime su muerte.
- Te recuerdo, los filosofos deben evitar morir.



