/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life-cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 15:30:04 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/29 12:20:13 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include <philo_bonus.h>
#include <thread_db.h>
#include <stdlib.h>

void	*death_checker(void *state_arg)
{
	t_state			*state;
	t_philosopher	*philosopher;
	long			time_since_eat;

	state = (t_state *)state_arg;
	philosopher = state->philosopher;
	while (!philosopher->is_dead)
	{
		time_since_eat = get_current_time() - philosopher->last_time_has_eaten;
		if ((int)time_since_eat > state->parameters->time_to_die)
		{
			philosopher_die(state);
			sem_post(state->simulation_end);
		}
		usleep(WAIT_FREQ);
	}
	return (NULL);
}

void	*eat_number_checker(void *state_arg)
{
	t_state			*state;
	t_philosopher	*philosopher;
	int				number_of_times_must_eat;
	int				*number_of_time_has_eaten;

	state = (t_state *)state_arg;
	philosopher = state->philosopher;
	number_of_times_must_eat = state->parameters->number_of_times_must_eat;
	number_of_time_has_eaten = &philosopher->number_of_time_has_eaten;
	if (number_of_times_must_eat == -1)
		return (NULL);
	while (*number_of_time_has_eaten < number_of_times_must_eat)
	{
		usleep(WAIT_FREQ);
	}
	sem_post(state->number_have_eaten_enough);
	return (NULL);
}

int	start_philosopher_checkers(t_state *state, thread_t *threads)
{
	int		result_death;
	int		result_eat;

	result_death = pthread_create(&threads[0], NULL, &death_checker, state);
	result_eat = pthread_create(&threads[1], NULL, &eat_number_checker, state);
	if (result_death != 0 || result_eater != 0)
	{
		sem_post(state->simulation_end);
		exit(ERROR_WHILE_CREATING_THREAD);
	}
	pthread_detach(threads[0]);
	pthread_detach(threads[1]);
	return (0);
}

void	*run_life_cycle(t_state *state)
{
	t_philosopher	*philosopher;
	thread_t		threads[2];

	start_philosopher_checkers(state, threads);
	philosopher = state->philosopher;
	if (philosopher->id % 2 == 0)
		wait_ms(state->parameters->time_to_eat / 2);
	while (philosopher->is_dead == false)
	{
		if (philosopher->state == THINKING)
			philosopher_eat(state);
		if (philosopher->state == SLEEPING)
			philosopher_sleep(state);
	}
	return (NULL);
}
