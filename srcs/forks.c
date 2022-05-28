/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:19:00 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/28 18:02:28 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <stdbool.h>

void	take_forks(t_state *state)
{
	sem_wait(state->forks);
	log_message(state, "has taken fork");
	sem_wait(state->forks);
	log_message(state, "has taken fork");
}

void	let_forks_go(t_state *state)
{
	sem_post(state->forks);
	sem_post(state->forks);
}