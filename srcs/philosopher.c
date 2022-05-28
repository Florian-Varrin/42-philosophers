/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:46:41 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/28 14:53:34 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <stdbool.h>

#include <philo_bonus.h>
#include <unistd.h>

t_philosopher	*init_philosopher(t_philosopher **philosopher, int id)
{
	*philosopher = (t_philosopher *)malloc(sizeof(t_philosopher));
	if (*philosopher == NULL)
		return (NULL);
	(*philosopher)->id = id;
	(*philosopher)->state = THINKING;
	(*philosopher)->number_of_time_has_eaten = 0;
	(*philosopher)->last_time_has_eaten = get_current_time();
	(*philosopher)->is_dead = false;
	return (*philosopher);
}

t_philosopher	*destroy_philosopher(t_philosopher *philosopher)
{
	free(philosopher);
	return (NULL);
}

int	init_philosophers(t_state *state)
{
	int		i;
	int		id;

	i = 0;
	while (i < state->parameters->number_of_philosophers)
	{
		id = fork();
		if (id == -1)
			return (ERROR_WHILE_FORKING_PROCESS);
		else if (id == 0)
		{
			init_philosopher(&state->philosopher, i + 1);
			break ;
		}
		i++;
	}
	return (0);
}
