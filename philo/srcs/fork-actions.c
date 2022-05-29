/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork-actions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:31:49 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/29 12:14:11 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdbool.h>

#include "philo.h"

t_fork	**set_needed_forks(t_fork **forks, t_state *state, int philosopher_id)
{
	if (philosopher_id == 1)
		forks[0] = state->forks[state->parameters->number_of_philosophers - 1];
	else
		forks[0] = state->forks[philosopher_id - 2];
	forks[1] = state->forks[philosopher_id - 1];
	return (forks);
}

void	take_fork(t_state *state, t_fork *fork, int *taken_forks, int id)
{
	if (fork->state == FREE)
	{
		pthread_mutex_lock(&state->forks_mutex);
		fork->state = USED;
		(*taken_forks)++;
		pthread_mutex_unlock(&state->forks_mutex);
		log_message(state, id, "has taken a fork", true);
	}
}

void	take_forks(t_state *state, t_philosopher *philosopher)
{
	t_fork			*forks[2];
	int				taken_forks;

	set_needed_forks(forks, state, philosopher->id);
	taken_forks = 0;
	while (taken_forks != 2)
	{
		take_fork(state, forks[0], &taken_forks, philosopher->id);
		take_fork(state, forks[1], &taken_forks, philosopher->id);
		usleep(WAIT_FREQ);
	}
}

void	let_forks_go(t_state *state, int id)
{
	t_fork		*forks[2];

	set_needed_forks(forks, state, id);
	forks[0]->state = FREE;
	forks[1]->state = FREE;
}
