/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher-actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:31:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/15 13:25:17 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>
#include "philosophers.h"

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
		log_message(state, id, "has taken a fork");
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

void	philosopher_eat(t_state *state, t_philosopher *philosopher)
{
	take_forks(state, philosopher);
	philosopher->state = EATING;
	log_message(state, philosopher->id, "is eating");
	philosopher->last_time_has_eaten = get_current_time();
	philosopher->number_of_time_has_eaten++;
	wait_ms(state->parameters->time_to_eat);
	let_forks_go(state, philosopher->id);
	philosopher->state = SLEEPING;
}

void	philosopher_sleep(t_state *state, t_philosopher *philosopher)
{
	log_message(state, philosopher->id, "is sleeping");
	wait_ms(state->parameters->time_to_sleep);
	philosopher->state = THINKING;
	log_message(state, philosopher->id, "is thinking");
}

void	philosopher_die(t_state *state, t_philosopher *philosopher)
{
	log_message(state, philosopher->id, "died");
	philosopher->is_dead = true;
}