/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:09:08 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/07 15:13:43 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <pthread.h>
#include <malloc.h>

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
		t_philosopher_state **philosopher_states
		)
{
	int		i;

	i = 0;
	while (i < state->parameters->number_of_philosophers)
	{
		if (pthread_create(&threads[i],
				NULL, &run_philosopher, philosopher_states[i]) != 0)
			return (exit_error(ERROR_WHILE_CREATING_THREAD,
					"Error while creating thread"));
		i++;
	}
	return (0);
}

int	join_threads(t_state *state, pthread_t *threads)
{
	int		i;

	i = 0;
	while (i < state->parameters->number_of_philosophers)
	{
		if (pthread_join(threads[i], NULL) != 0)
			return (exit_error(ERROR_WHILE_JOINING_THREAD,
					"Error while creating thread"));
		i++;
	}
	return (0);
}
