/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:56:53 by fvarrin           #+#    #+#             */
/*   Updated: 2022/04/24 14:47:55 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <stdbool.h>

#include <philo_bonus.h>

t_parameters	*init_parameters(
		t_parameters *parameters,
		int argc,
		char **argv
	)
{
	parameters = malloc(sizeof(t_parameters));
	if (parameters == NULL)
		return (NULL);
	parameters->number_of_philosophers = ft_atoi(argv[1]);
	parameters->time_to_die = ft_atoi(argv[2]);
	parameters->time_to_eat = ft_atoi(argv[3]);
	parameters->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		parameters->number_of_times_must_eat = ft_atoi(argv[5]);
	else
		parameters->number_of_times_must_eat = -1;
	return (parameters);
}

_Bool	check_parameters_constraints(t_parameters *parameters)
{
	if (parameters->number_of_philosophers < 1)
		return (false);
	if (parameters->time_to_die < 0)
		return (false);
	if (parameters->time_to_eat < 0)
		return (false);
	if (parameters->time_to_sleep < 0)
		return (false);
	return (true);
}

int	parse_parameters(t_parameters **parameters, int argc, char **argv)
{
	*parameters = init_parameters(*parameters, argc, argv);
	if (*parameters == NULL)
		return (ERROR_WHILE_ALLOCATING_MEMORY);
	if (check_parameters_constraints(*parameters))
		return (0);
	else
		return (INVALID_ARGUMENTS);
}

t_parameters	*destroy_parameters(t_parameters *parameters)
{
	free(parameters);
	return (NULL);
}
