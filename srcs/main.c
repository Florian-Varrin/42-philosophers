/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:41:28 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/28 13:45:00 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
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

int main(int argc, char **argv)
{
	t_state				*state;
	int					state_init_result;

	if (argc != 5 && argc != 6)
		return (print_usage(INVALID_ARGUMENTS));
	state = NULL;
	state_init_result = init_state(&state, argc, argv);
	if (state_init_result != 0)
	{
		destroy_state(state);
		return (state_init_result);
	}
	return (0);
}