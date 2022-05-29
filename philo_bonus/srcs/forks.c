/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:19:00 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/28 18:08:35 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <stdbool.h>

void	take_forks(t_state *state)
{
	sem_wait(state->forks);
	log_message(state, "has taken fork", true);
	sem_wait(state->forks);
	log_message(state, "has taken fork", true);
}

void	let_forks_go(t_state *state)
{
	sem_post(state->forks);
	sem_post(state->forks);
}