/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher-actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:31:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/08 19:09:46 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "philosophers.h"

int	*set_forks_ids(int *fork_ids, t_state *state, int philosopher_id)
{
	if (philosopher_id == 1)
		fork_ids[0] = state->parameters->number_of_philosophers;
	else
		fork_ids[0] = philosopher_id - 1;
	fork_ids[1] = philosopher_id;
	return (fork_ids);
}

void	take_forks(t_state *state, int id)
{
	int				fork_ids[2];

	set_forks_ids(fork_ids, state, id);
	state->forks[fork_ids[0] - 1]->state = USED;
	log_message(id, "has taken a fork");
	state->forks[fork_ids[1] - 1]->state = USED;
	if (fork_ids[0] != fork_ids[1])
		log_message(id, "has taken a fork");
}

void	let_forks_go(t_state *state, int id)
{
	int				fork_ids[2];

	set_forks_ids(fork_ids, state, id);
	state->forks[fork_ids[0] - 1]->state = FREE;
	state->forks[fork_ids[1] - 1]->state = FREE;
}

int	philosopher_eat(t_state *state, t_philosopher *philosopher)
{
	int		id;
	int		time_spend_eating;

	id = philosopher->id;
	pthread_mutex_lock(&state->forks_mutex);
	while (!check_if_can_take_forks(state, id))
	{
		if (check_if_is_dead(state, id) == true)
			return (philosopher_die(philosopher));
	}
	time_spend_eating = 0;
	take_forks(state, id);
	pthread_mutex_unlock(&state->forks_mutex);
	philosopher->state = EATING;
	log_message(id, "is eating");
	philosopher->last_time_has_eaten = get_current_time();
	while (time_spend_eating < state->parameters->time_to_eat)
	{
		wait_ms(10);
		time_spend_eating += 10;
		if (check_if_is_dead(state, id) == true)
			return (philosopher_die(philosopher));
	}
	philosopher->number_of_time_has_eaten++;
	let_forks_go(state, id);
	philosopher->state = SLEEPING;
	return (0);
}

int	philosopher_sleep(t_state *state, t_philosopher *philosopher)
{
	int		id;
	int		time_has_spend_sleeping;

	id = philosopher->id;
	time_has_spend_sleeping = 0;
	log_message(id, "is sleeping");
	while (time_has_spend_sleeping < state->parameters->time_to_sleep)
	{
		wait_ms(10);
		time_has_spend_sleeping += 10;
		if (check_if_is_dead(state, id) == true)
			return (philosopher_die(philosopher));
	}
	philosopher->state = THINKING;
	log_message(id, "is thinking");
	return (0);
}

int	philosopher_die(t_philosopher *philosopher)
{
	philosopher->is_dead = true;
	log_message(philosopher->id, "died");
	return (-1);
}