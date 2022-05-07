/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher-state.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 14:31:03 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/07 14:57:22 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include "philosophers.h"

t_philosopher_state	*init_philosopher_state(int id, t_state *state)
{
	t_philosopher_state	*philosopher_state;

	philosopher_state = malloc(sizeof(t_philosopher_state));
	philosopher_state->id = id;
	philosopher_state->state = state;
	return (philosopher_state);
}

t_philosopher_state	**init_philosopher_states(t_state *state)
{
	int					i;
	int					number_of_philosophers;
	t_philosopher_state	**philosopher_states;

	number_of_philosophers = state->parameters->number_of_philosophers;
	philosopher_states = (t_philosopher_state **)malloc(
			sizeof(t_philosopher_state *) * number_of_philosophers);
	i = 0;
	while (i < state->parameters->number_of_philosophers)
	{
		philosopher_states[i] = init_philosopher_state(i + 1, state);
		i++;
	}
	return (philosopher_states);
}

t_philosopher_state	*destroy_philosopher_states(
		t_philosopher_state **philosopher_states
	)
{
	int		i;
	int		number_of_philosophers;

	i = 0;
	number_of_philosophers
		= philosopher_states[0]->state->parameters->number_of_philosophers;
	while (i < number_of_philosophers)
	{
		free(philosopher_states[i]);
		i++;
	}
	free(philosopher_states);
	return (NULL);
}
