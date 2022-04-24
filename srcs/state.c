/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 14:10:43 by fvarrin           #+#    #+#             */
/*   Updated: 2022/04/24 14:59:11 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include "philosophers.h"

int	init_state(t_state **state, int argc, char **argv)
{
	t_parameters	*parameters;

	*state = malloc(sizeof(t_state));
	if (*state == NULL)
		return (ERROR_WHILE_ALLOCATING_MEMORY);
	(*state)->parameters = NULL;
	(*state)->philosophers = NULL;
	(*state)->forks = NULL;
	parameters = (*state)->parameters;
	if (parse_parameters(&parameters, argc, argv) != 0)
		return (INVALID_ARGUMENTS);
	(*state)->parameters = parameters;
	if (init_philosophers(*state, parameters) != 0)
		return (ERROR_WHILE_ALLOCATING_MEMORY);
	if (init_forks(*state, parameters) != 0)
		return (ERROR_WHILE_ALLOCATING_MEMORY);
	return (0);
}

t_state	*destroy_state(t_state *state)
{
	if (state->parameters == NULL)
	{
		free(state);
		return (NULL);
	}
	if (state->philosophers == NULL)
	{
		free(state->parameters);
		free(state);
		return (NULL);
	}
	destroy_philosophers(state);
	if (state->forks == NULL)
	{
		free(state->parameters);
		free(state);
		return (NULL);
	}
	destroy_forks(state);
	free(state->parameters);
	free(state);
	return (NULL);
}
