/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/28 17:14:08 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/28 17:19:27 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo_bonus.h>
#include <stddef.h>

void	*check_all_have_eaten_enough(void *state_arg)
{
	t_state		*state;
	int			i;

	state = (t_state *)state_arg;
	i = 0;
	while (i < state->parameters->number_of_philosophers)
	{
		sem_wait(state->number_have_eaten_enough);
		i++;
	}
	sem_post(state->simulation_end);
	return (NULL);
}
