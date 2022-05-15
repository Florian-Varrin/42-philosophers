/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:53:12 by fvarrin           #+#    #+#             */
/*   Updated: 2022/04/24 14:59:34 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include "philosophers.h"

static t_fork	*init_fork(t_fork **fork, int id)
{
	*fork = (t_fork *)malloc(sizeof(t_fork));
	if (*fork == NULL)
		return (NULL);
	(*fork)->id = id;
	(*fork)->state = FREE;
	return (*fork);
}

static t_fork	*destroy_fork(t_fork *fork)
{
	free(fork);
	return (NULL);
}

int	init_forks(t_state *state, t_parameters *parameters)
{
	int		i;

	state->forks = malloc(
			sizeof(t_fork *) * parameters->number_of_philosophers);
	if (state->forks == NULL)
		return (ERROR_WHILE_ALLOCATING_MEMORY);
	i = 0;
	while (i < parameters->number_of_philosophers)
	{
		init_fork(&(state->forks[i]), i + 1);
		i++;
	}
	return (0);
}

void	destroy_forks(t_state *state)
{
	int		i;

	i = 0;
	while (i < state->parameters->number_of_philosophers)
		destroy_fork(state->forks[i++]);
	free(state->forks);
}
