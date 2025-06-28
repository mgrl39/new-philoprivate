/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: meghribe <meghribe@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 06:53:15 by meghribe          #+#    #+#             */
/*   Updated: 2025/06/28 11:41:32 by meghribe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>

/**
 * Cambio 1: Ajustando el ordend e toma de tenedores.
 *
 * El problema clasico de los filosofos tiene un desafio de sincronizacion:
 * Si todos los filosofos toman primero elt enedor izquierdo y luego el derecho,
 * podria ocurrir un deadlock (todos toman un tenedor y esperan eternamente).
 *
 * Esta solucion hace que los filosofos pares e impares tomen todos los tenedores
 * en orden opuesto para evitar ese bloqueo.
 *
 * Sin embargo, aun asi el filosofo 1 podria tomar ambos tenedores antes que
 * e filosofo 2 pueda tomar alguno, causando que el filosofo 2 muera de hambre.
 */
/* Los filosofos pares toman primero el tenedor derecho */
/* Despues toman el tenedor izquierdo */
/* Los filosofos impares toman primero el tenedor izquierdo */
/* Despues toman el tenedor derecho */
/*
   debug_print("Filosofo %d tomando tenedor izquierdo", philo->id);
   pthread_mutex_lock(philo->forks[LEFT]);
   print_status(philo, MSG_FORK);
   if (philo->forks[RIGHT])
   {
   debug_print("Filosofo %d tomando tenedor derecho", philo->id);
   pthread_mutex_lock(philo->forks[RIGHT]);
   print_status(philo, MSG_FORK);
   }
   else
   debug_print("Filosofo %d no tiene tenedor derecho", philo->id);
*/
static void	take_forks(t_philo *philo)
{
	if (!philo)
	{
		debug_print("Error: philo es NULL en take_forks");
		return ;
	}
	if (philo->id % 2 == 0)
	{
		if (philo->forks[RIGHT])
		{
			pthread_mutex_lock(philo->forks[RIGHT]);
			print_status(philo, MSG_FORK);
		}
		pthread_mutex_lock(philo->forks[LEFT]);
		print_status(philo, MSG_FORK);
	}
	else
	{
		pthread_mutex_lock(philo->forks[LEFT]);
		print_status(philo, MSG_FORK);
		if (philo->forks[RIGHT])
		{
			pthread_mutex_lock(philo->forks[RIGHT]);
			print_status(philo, MSG_FORK);
		}
	}
}

/**
 * Verificacion importante: Si un filosoo no tiene tenedor derecho,
 * (caso de un solo filosofo), debe liberar el tenedor izquierdo
 * ya que nunca podra comer.
 */
//pthread_mutex_unlock(philo->forks[LEFT]);
/**
 * Importante: actualizamos el tiempop de la ultima comida.
 * Esto es critico para el monitoreo de muerte por hambre
 */
/**
 * El filosofo come durante time_to_eat milisegundos.
 * Esto simula el tiempo que tarda en comer
 */
/**
 * Importante: Liberamos los tenedores en el orden invverso
 * auq ue los tomamos para reducir la probiabilidad de deadlock
 */
static void	eat(t_philo *philo)
{
	if (!philo)
	{
		debug_print("Error: philo es NULL en eat");
		return ;
	}
	if (!philo->forks[RIGHT])
	{
		debug_print("Filosofo %d no uede comer (solo tiene un tenedor)"
			, philo->id);
		return ;
	}
	debug_print("Filosofo %d comienodo", philo->id);
	print_status(philo, MSG_EAT);
	pthread_mutex_lock(&philo->table->meal_lock);
	philo->last_meal_time = get_time();
	philo->meals_eaten++;
	debug_print("Filosofo %d actualizado: comidas=%d, ultimo tiempo=%ld",
		philo->id, philo->meals_eaten, philo->last_meal_time);
	pthread_mutex_unlock(&philo->table->meal_lock);
	usleep(philo->table->time_to_eat * 1000);
	debug_print("Filosofo %d soltando tenedores", philo->id);
	pthread_mutex_unlock(philo->forks[RIGHT]);
	pthread_mutex_unlock(philo->forks[LEFT]);
}

/**
 * El filosofo duerme durante time_to_sleep milisegundos.
 * Esto da tiempo a otros filosofs para tomar tenedores
 */
static void	sleep_and_think(t_philo *philo)
{
	if (!philo)
		return ;
	print_status(philo, MSG_SLEEP);
	usleep(philo->table->time_to_sleep * 1000);
	print_status(philo, MSG_THINK);
}

/**
 * CAMBIO 2: Aumentar el tiempo de espera par afilosofso pares.
 *
 * Este retraso es crucial para evitar la inanicion. Los filosofso pares 
 * esperan un poco mas para dar ventaja a los impares y que puedan tomar
 * sus tenedores primero.
 *
 * 1000 microsegundos (1ms) es muy poco tiempo y puede que no ssea suficiente
 * para permitir que los filosofos impares agarren sus tenedores primero.
 */
/* Bucle principal de la vida del filosofo */
/**
 * Caso especial: filosof cno un solo tenedor no puede comer, asi que solo espera a morir */
void	*philo_loop(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	debug_print("Filosofo %d iniciado", philo->id);
	if (philo->id % 2 == 0)
		usleep(10000);
	while (!check_death_flag(philo->table) && (philo->table->num_meals == -1 \
				|| philo->meals_eaten < philo->table->num_meals))
	{
		debug_print("Filosofo %d intentando comer tenedores", philo->id);
		take_forks(philo);
		debug_print("Filosofo %d intentando comer", philo->id);
		eat(philo);
		if (philo->forks[RIGHT])
		{
			debug_print("filosofo %d intentando dormir y pensar", philo->id);
			sleep_and_think(philo);
		}
		else
		{
			debug_print("Filosofo %d esperando morir (sin tenedor derecho)", philo->id);
			while (!check_death_flag(philo->table))
				usleep(1000);
			pthread_mutex_unlock(philo->forks[LEFT]);
			break ;
		}
	}
	return (NULL);
}
