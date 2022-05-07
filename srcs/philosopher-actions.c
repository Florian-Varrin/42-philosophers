/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher-actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:31:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/07 13:56:38 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "philosophers.h"

static int *set_forks_ids(int *fork_ids, t_state *state, int philosopher_id)
{
	if (philosopher_id == 1)
		fork_ids[0] = state->parameters->number_of_philosophers;
	else
		fork_ids[0] = philosopher_id - 1;
	fork_ids[1] = philosopher_id;
	return (fork_ids);
}

_Bool check_if_can_take_forks(t_state *state, int philosopher_id)
{
	int		i;
	int		fork_ids[2];
	int		fork_id;
	int		tested_fork;

	set_forks_ids(fork_ids, state, philosopher_id);
	i = 0;
	tested_fork = 0;
	while (i < state->parameters->number_of_philosophers && tested_fork < 2)
	{
		fork_id = state->forks[i]->id;
		if (fork_id == fork_ids[0] || fork_id == fork_ids[1])
		{
			if (state->forks[i]->state == USED)
				return (false);
			tested_fork++;
		}
		i++;
	}
	return (true);
}

void take_forks(t_state *state, int philosopher_id)
{
	int				fork_ids[2];
	t_philosopher	*philosopher;

	while (!check_if_can_take_forks(state, philosopher_id)) {}
	set_forks_ids(fork_ids, state, philosopher_id);
	pthread_mutex_lock(state->forks_mutex);
	state->forks[fork_ids[0]]->state = USED;
	state->forks[fork_ids[1]]->state = USED;
	philosopher = get_philosopher_from_id(state->philosophers, philosopher_id);
	philosopher->state = EATING;
	pthread_mutex_unlock(state->forks_mutex);
}
