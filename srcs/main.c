/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:41:28 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/28 14:54:40 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "philo_bonus.h"

int	print_usage(int exit_code)
{
	printf(
			"usage: %s [%s] [%s] [%s] [%s] [%s]",
			BIN_NAME,
			"number_of_philosophers",
			"time_to_die",
			"time_to_eat",
			"time_to_sleep",
			"number_of_times_each_philosopher_must_eat"
	);
	return (exit_code);
}

int	exit_error(int exit_code, char *message)
{
	write(STDERR_FILENO, message, ft_strlen(message));
	return (exit_code);
}

int run(t_state *state)
{
	int		philosopher_result;

	philosopher_result = init_philosophers(state);
	if (philosopher_result != 0)
		return (philosopher_result);
	if (!state->philosopher)
	{
		state->forks = sem_open(FORKS_SEM_NAME, O_CREAT | O_EXCL, 0777, state->parameters->number_of_philosophers);
		if (state->forks == SEM_FAILED)
			return (ERROR_WHILE_OPENING_SEMAPHORE);
	}
	else
	{
		state->forks = sem_open(FORKS_SEM_NAME, 0);
		if (state->forks == SEM_FAILED)
			return (ERROR_WHILE_OPENING_SEMAPHORE);
	}
}

int main(int argc, char **argv)
{
	t_state				*state;
	int					state_init_result;
	int					run_result;

	if (argc != 5 && argc != 6)
		return (print_usage(INVALID_ARGUMENTS));
	state = NULL;
	state_init_result = init_state(&state, argc, argv);
	if (state_init_result != 0)
	{
		destroy_state(state);
		return (state_init_result);
	}
	run_result = run(state);
	destroy_state(state);
	return (run_result);
}