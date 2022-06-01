/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:09:08 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/01 11:20:02 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <pthread.h>
#include <stdlib.h>

pthread_t	*init_threads(t_state *state)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(
			sizeof(pthread_t) * state->parameters->number_of_philosophers);
	return (threads);
}

pthread_t	*destroy_threads(pthread_t *threads)
{
	free(threads);
	return (NULL);
}

int	create_threads(
		t_state *state,
		pthread_t *threads,
		t_life_cycle_state **philosopher_states
		)
{
	int		i;

	i = 0;
	while (i < state->parameters->number_of_philosophers)
	{
		if (pthread_create(&threads[i],
				NULL, &run_life_cycle, philosopher_states[i]) != 0)
			return (exit_error(ERROR_WHILE_CREATING_THREAD,
					"Error while creating thread"));
		pthread_detach(threads[i]);
		i++;
	}
	return (0);
}
