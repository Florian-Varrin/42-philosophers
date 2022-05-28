/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher-check.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:31:00 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/08 19:32:50 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

_Bool	check_if_is_dead(t_state *state, int philosopher_id)
{
	t_philosopher	*philosopher;
	long			time_since_eaten;

	philosopher = get_philosopher_from_id(state->philosophers, philosopher_id);
	time_since_eaten = get_current_time() - philosopher->last_time_has_eaten;
	return ((int)time_since_eaten > state->parameters->time_to_die);
}
