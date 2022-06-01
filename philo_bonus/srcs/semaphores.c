/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphores.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 15:27:11 by fvarrin           #+#    #+#             */
/*   Updated: 2022/06/01 11:48:03 by fvarrin          ###   ########.fr       */
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
	sem_unlink(CAN_WRITE_SEM_NAME);
}

void	create_semaphores(t_state *state)
{
	int	flags;
	int	mode;

	flags = O_CREAT | O_EXCL;
	mode = 0600;
	state->forks = sem_open(FORKS_SEM_NAME, flags, mode,
			state->parameters->number_of_philosophers);
	if (state->forks == SEM_FAILED)
		exit(ERROR_WHILE_OPENING_SEMAPHORE);
	state->simulation_end = sem_open(SIM_END_SEM_NAME,
			flags, mode, 0);
	if (state->simulation_end == SEM_FAILED)
		exit(ERROR_WHILE_OPENING_SEMAPHORE);
	state->number_have_eaten_enough = sem_open(EATEN_ENOUGH_SEM_NAME,
			flags, mode, 0);
	if (state->number_have_eaten_enough == SEM_FAILED)
		exit(ERROR_WHILE_OPENING_SEMAPHORE);
	state->can_write = sem_open(CAN_WRITE_SEM_NAME, flags, mode, 1);
	if (state->can_write == SEM_FAILED)
		exit(ERROR_WHILE_OPENING_SEMAPHORE);
}

void	destroy_semaphores(t_state *state)
{
	sem_close(state->forks);
	sem_close(state->simulation_end);
	sem_close(state->number_have_eaten_enough);
	sem_close(state->can_write);
}
