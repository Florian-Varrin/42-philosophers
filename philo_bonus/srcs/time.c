/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 10:19:49 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/28 13:49:23 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

#include <philo_bonus.h>

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
}

void	wait_ms(int ms)
{
	long	start_time;

	start_time = get_current_time();
	while (get_current_time() - start_time < ms)
		usleep(WAIT_FREQ);
}
