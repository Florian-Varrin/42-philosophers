/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 13:01:13 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/15 12:57:20 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>

#include "philosophers.h"

_Bool	ft_isspace(const char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (true);
	return (false);
}

int	ft_atoi(const char *str)
{
	int		sign;
	int		res;

	while (ft_isspace(*str))
		str++;
	sign = 1;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res *= 10;
		res += (*str - 48);
		str++;
	}
	return (res * sign);
}

int	ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	log_message(t_state *state, int id, char *message)
{
	long			current_time;
	long			time_since_start;
	t_philosopher	*philosopher;

	philosopher = get_philosopher_from_id(state->philosophers, id);
	if (philosopher->is_dead == true)
		return;
	current_time = get_current_time();
	time_since_start = current_time - state->start_time;
	printf("%6ld %3d %s\n", time_since_start, id, message);
}