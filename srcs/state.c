/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:10:43 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/28 13:55:23 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

#include <philo_bonus.h>

int	init_state(t_state **state, int argc, char **argv)
{
	t_parameters	*parameters;

	*state = malloc(sizeof(t_state));
	if (*state == NULL)
		return (ERROR_WHILE_ALLOCATING_MEMORY);
	sem_unlink(FORKS_SEM_NAME);
	(*state)->parameters = NULL;
	(*state)->philosopher = NULL;
	(*state)->forks = NULL;
	parameters = (*state)->parameters;
	if (parse_parameters(&parameters, argc, argv) != 0)
		return (INVALID_ARGUMENTS);
	(*state)->parameters = parameters;
	(*state)->start_time = get_current_time();
	return (0);
}

t_state	*destroy_state(t_state *state)
{
	if (state->parameters == NULL)
	{
		free(state);
		return (NULL);
	}
	if (state->philosopher == NULL)
	{
		free(state->parameters);
		free(state);
		return (NULL);
	}
	destroy_philosopher(state->philosopher);
	if (state->forks == NULL)
	{
		free(state->parameters);
		free(state);
		return (NULL);
	}
	sem_destroy(state->forks);
	free(state->parameters);
	free(state);
	return (NULL);
}
