/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:27:11 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/28 18:09:22 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <semaphore.h>
#include <fcntl.h>

#include <philo_bonus.h>
#include <stdlib.h>
#include <stdio.h>

void	unlink_semaphores(void)
{
	sem_unlink(FORKS_SEM_NAME);
	sem_unlink(SIM_END_SEM_NAME);
	sem_unlink(EATEN_ENOUGH_SEM_NAME);
}

void	create_semaphores(t_state *state)
{
	state->forks = sem_open(FORKS_SEM_NAME, O_CREAT | O_EXCL, 0777,
							state->parameters->number_of_philosophers);
	if (state->forks == SEM_FAILED)
		exit(ERROR_WHILE_OPENING_SEMAPHORE);
	state->simulation_end = sem_open(SIM_END_SEM_NAME,
									 O_CREAT | O_EXCL, 0777, 0);
	if (state->simulation_end == SEM_FAILED)
		exit(ERROR_WHILE_OPENING_SEMAPHORE);
	state->number_have_eaten_enough = sem_open(EATEN_ENOUGH_SEM_NAME,
											   O_CREAT | O_EXCL, 0777, 0);
	if (state->number_have_eaten_enough == SEM_FAILED)
		exit(ERROR_WHILE_OPENING_SEMAPHORE);
}

void	destroy_semaphores(t_state *state)
{
	sem_destroy(state->forks);
	sem_destroy(state->simulation_end);
	sem_destroy(state->number_have_eaten_enough);
}