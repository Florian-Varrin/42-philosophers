/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher-actions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:31:35 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/28 18:09:00 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#include <philo_bonus.h>

void	philosopher_eat(t_state *state)
{
	t_philosopher	*philosopher;

	philosopher = state->philosopher;
	take_forks(state);
	philosopher->state = EATING;
	log_message(state, "is eating");
	philosopher->last_time_has_eaten = get_current_time();
	philosopher->number_of_time_has_eaten++;
	wait_ms(state->parameters->time_to_eat);
	let_forks_go(state);
	philosopher->state = SLEEPING;
}

void	philosopher_sleep(t_state *state)
{
	t_philosopher	*philosopher;

	philosopher = state->philosopher;
	log_message(state, "is sleeping");
	wait_ms(state->parameters->time_to_sleep);
	philosopher->state = THINKING;
	log_message(state, "is thinking");
}

void	philosopher_die(t_state *state)
{
	t_philosopher	*philosopher;

	philosopher = state->philosopher;
	log_message(state, "died");
	philosopher->is_dead = true;
}
