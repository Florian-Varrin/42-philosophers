/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:41:28 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/29 12:16:52 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h>
#include <stdlib.h>
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

void	kill_processes(t_state *state)
{
	int		i;

	i = 0;
	while (i < state->parameters->number_of_philosophers)
	{
		kill(state->pids[i], SIGKILL);
		i++;
	}
}

int	run(t_state *state)
{
	int			philosopher_result;
	pthread_t	eat_checker;

	philosopher_result = init_philosophers(state);
	if (philosopher_result != 0)
		return (philosopher_result);
	if (!state->philosopher)
	{
		if (pthread_create(&eat_checker, NULL,
				&check_all_have_eaten_enough, state) != 0)
			exit(ERROR_WHILE_CREATING_THREAD);
		pthread_detach(eat_checker);
		sem_wait(state->simulation_end);
		kill_processes(state);
	}
	else
	{
		run_life_cycle(state);
	}
	return (0);
}

int	main(int argc, char **argv)
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
	create_semaphores(state);
	run_result = run(state);
	destroy_state(state);
	return (run_result);
}
