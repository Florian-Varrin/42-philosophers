/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:31:04 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/15 13:30:34 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

#include <stdio.h>
#include <unistd.h>

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

int	run(t_state *state)
{
	int					thread_result;
	pthread_t			*threads;
	t_life_cycle_state	**philosopher_states;

	threads = init_threads(state);
	philosopher_states = init_philosopher_states(state);
	thread_result = create_threads(state, threads, philosopher_states);
	if (thread_result != 0)
		return (thread_result);
	while (!check_if_a_philosopher_is_dead(state)
		&& !check_if_all_have_eaten_enough(state))
	{
		usleep(WAIT_FREQ);
	}
	destroy_philosopher_states(philosopher_states);
	destroy_threads(threads);
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
	run_result = run(state);
	destroy_state(state);
	return (run_result);
}
