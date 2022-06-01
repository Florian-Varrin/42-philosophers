/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:46:41 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/01 11:44:03 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include "philo.h"

static t_philosopher	*init_philosopher(t_philosopher **philosopher, int id)
{
	*philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (*philosopher == NULL)
		return (NULL);
	(*philosopher)->id = id;
	(*philosopher)->state = THINKING;
	(*philosopher)->number_of_time_has_eaten = 0;
	(*philosopher)->last_time_has_eaten = get_current_time();
	(*philosopher)->is_dead = false;
	return (*philosopher);
}

static t_philosopher	*destroy_philosopher(t_philosopher *philosopher)
{
	free(philosopher);
	return (NULL);
}

int	init_philosophers(t_state *state, t_parameters *parameters)
{
	int		i;

	state->philosophers = malloc(
			sizeof(t_philosopher *) * parameters->number_of_philosophers);
	if (state->philosophers == NULL)
		return (ERROR_WHILE_ALLOCATING_MEMORY);
	i = 0;
	while (i < parameters->number_of_philosophers)
	{
		init_philosopher(&(state->philosophers[i]), i + 1);
		i++;
	}
	return (0);
}

void	destroy_philosophers(t_state *state)
{
	int		i;

	i = 0;
	while (i < state->parameters->number_of_philosophers)
		destroy_philosopher(state->philosophers[i++]);
	free(state->philosophers);
}

t_philosopher	*get_philosopher_from_id(t_philosopher **philosophers, int id)
{
	return (philosophers[id - 1]);
}
