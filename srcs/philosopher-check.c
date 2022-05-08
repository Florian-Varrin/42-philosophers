/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher-check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:31:00 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/08 18:11:41 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include "philosophers.h"

_Bool	check_if_can_take_forks(t_state *state, int philosopher_id)
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
			{
				return (false);
			}
			tested_fork++;
		}
		i++;
	}
	return (true);
}

_Bool	check_if_is_dead(t_state *state, int philosopher_id)
{
	t_philosopher	*philosopher;
	long			time_since_eaten;

	philosopher = get_philosopher_from_id(state->philosophers, philosopher_id);
	time_since_eaten = get_current_time() - philosopher->last_time_has_eaten;
	return ((int)time_since_eaten > state->parameters->time_to_die);
}