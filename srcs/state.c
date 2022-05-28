/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:10:43 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/28 17:58:05 by fvarrin          ###   ########.fr       */
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
	unlink_semaphores();
	(*state)->parameters = NULL;
	(*state)->philosopher = NULL;
	(*state)->forks = NULL;
	(*state)->simulation_end = NULL;
	(*state)->number_have_eaten_enough = NULL;
	parameters = (*state)->parameters;
	if (parse_parameters(&parameters, argc, argv) != 0)
		return (INVALID_ARGUMENTS);
	(*state)->parameters = parameters;
	(*state)->start_time = get_current_time();
	(*state)->pids = malloc(sizeof(int) * parameters->number_of_philosophers);
	return (0);
}

t_state	*destroy_state(t_state *state)
{
	if (state->parameters == NULL)
	{
		free(state);
		return (NULL);
	}
	if (state->philosopher != NULL)
		destroy_philosopher(state->philosopher);
	destroy_semaphores(state);
	free(state->pids);
	free(state->parameters);
	free(state);
	return (NULL);
}
