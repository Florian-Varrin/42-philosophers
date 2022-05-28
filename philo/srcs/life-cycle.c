/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life-cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:30:04 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/15 13:34:25 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include "philo.h"

void	*run_life_cycle(void *philosopher_state)
{
	int				id;
	t_state			*state;
	t_philosopher	*philosopher;

	state = ((t_life_cycle_state *)philosopher_state)->state;
	id = ((t_life_cycle_state *)philosopher_state)->id;
	philosopher = get_philosopher_from_id(state->philosophers, id);
	if (id % 2 == 0)
		wait_ms(state->parameters->time_to_eat / 2);
	while (philosopher->is_dead == false)
	{
		if (philosopher->state == THINKING)
			philosopher_eat(state, philosopher);
		if (philosopher->state == SLEEPING)
			philosopher_sleep(state, philosopher);
	}
	return (NULL);
}

_Bool	check_if_a_philosopher_is_dead(t_state *state)
{
	int		i;

	i = 0;
	while (i < state->parameters->number_of_philosophers)
	{
		if (check_if_is_dead(state, state->philosophers[i]->id) == true)
		{
			philosopher_die(state, state->philosophers[i]);
			return (true);
		}
		i++;
	}
	return (false);
}

_Bool	check_if_all_have_eaten_enough(t_state *state)
{
	int		i;
	int		number_of_times_must_eat;
	_Bool	all_have_eaten_enough;

	number_of_times_must_eat = state->parameters->number_of_times_must_eat;
	if (number_of_times_must_eat == -1)
		return (false);
	i = 0;
	all_have_eaten_enough = true;
	while (i < state->parameters->number_of_philosophers)
	{
		if (state->philosophers[i]->number_of_time_has_eaten
			< number_of_times_must_eat)
			all_have_eaten_enough = false;
		i++;
	}
	return (all_have_eaten_enough);
}
