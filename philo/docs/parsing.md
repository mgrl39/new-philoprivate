# Pruebas de parseo de argumentos

## Caso 1: Número incorrecto de argumentos
Comando: `./philo`
```
Error: Usage: ./philo n_philos t_die t_eat t_sleep [n_meals]
```

## Caso 2: Argumentos no numéricos
Comando: `./philo abc 800 200 200`
```
Error: 'abc' contains non-numeric characters. Please use only digits.
```

## Caso 3: Valores negativos
Comando: `./philo 5 -800 200 200`
```
Error: '-800' is a negative number. Please use only positive values.
```

## Caso 4: Valores demasiado grandes
Comando: `./philo 5 9999999999 200 200`
```
Error: '9999999999' is too large. Maximum allowed value is 2147483647.
```

## Caso 5: Filósofos igual a cero
Comando: `./philo 0 800 200 200`
```
Error: Number of philosophers cannot be zero
```

## Caso 6: Tiempo para morir igual a cero
Comando: `./philo 5 0 200 200`
```
Error: time to die (0) cannot be zero.
```

## Caso 7: Tiempo para comer igual a cero
Comando: `./philo 5 800 0 200`
```
Error: time to eat (0) cannot be zero.
```

## Caso 8: Tiempo para dormir igual a cero
Comando: `./philo 5 800 200 0`
```
Error: time to sleep (0) cannot be zero.
```

## Caso 9: Número de comidas con caracteres no numéricos
Comando: `./philo 5 800 200 200 abc`
```
Error: 'abc' contains non-numeric characters. Please use only digits.
```

## Caso 10: Número de comidas negativo
Comando: `./philo 5 800 200 200 -5`
```
Error: '-5' is a negative number. Please use only positive values.
```

## Caso 11: Número de comidas igual a cero (válido, pero especial)
Comando: `./philo 5 800 200 200 0`
```
(Este caso no da error, se interpreta como "infinito")
```

## Caso 12: Mezcla de errores (se muestra el primer error encontrado)
Comando: `./philo abc -800 xyz 0`
```
Error: 'abc' contains non-numeric characters. Please use only digits.
```

# Funcionamiento correcto

Cuando todos los argumentos son válidos, no se muestra ningún mensaje de error y el programa continúa ejecutándose normalmente.

Comando: `./philo 5 800 200 200`
```
(La simulación inicia correctamente)
```

Comando: `./philo 5 800 200 200 10`
```
(La simulación inicia correctamente y termina después de que cada filósofo ha comido 10 veces)
```
