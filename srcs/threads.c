/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:09:08 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/07 14:47:46 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#include <pthread.h>
#include <malloc.h>

pthread_t	*init_threads(t_state *state)
{
	pthread_t	*threads;

	threads = (pthread_t *)malloc(
			sizeof(pthread_t) * state->parameters->number_of_philosophers);
	return (threads);
}

pthread_t	*destroy_threads(pthread_t *threads)
{
	free(threads);
	return (NULL);
}
