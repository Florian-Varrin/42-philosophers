/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:31:04 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/07 15:12:00 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

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
	t_philosopher_state	**philosopher_states;

	threads = init_threads(state);
	philosopher_states = init_philosopher_states(state);
	thread_result = create_threads(state, threads, philosopher_states);
	if (thread_result != 0)
		return (thread_result);
	thread_result = join_threads(state, threads);
	if (thread_result != 0)
		return (thread_result);
	destroy_philosopher_states(philosopher_states);
	destroy_threads(threads);
	return (0);
}

int	main(int argc, char **argv)
{
	t_state				*state;
	int					state_init_result;
	int					run_result;

	if (argc != 4 && argc != 5)
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
