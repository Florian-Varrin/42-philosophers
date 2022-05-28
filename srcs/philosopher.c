/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 12:46:41 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/28 13:42:57 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include <stdbool.h>

#include <philo_bonus.h>

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