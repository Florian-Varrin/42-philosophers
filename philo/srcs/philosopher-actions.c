/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher-actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:31:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/15 13:32:28 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include "philo.h"

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
