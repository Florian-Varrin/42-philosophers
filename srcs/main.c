/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 14:31:04 by                   #+#    #+#             */
/*   Updated: 2022/04/24 12:43:27 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <stdio.h>

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

int	main(int argc, char **argv)
{
	if (argc != 4 && argc != 5)
		return (print_usage(INVALID_ARGUMENTS));
	(void) argv;
	return (0);
}
