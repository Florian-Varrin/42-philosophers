/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:05:45 by                   #+#    #+#             */
/*   Updated: 2022/04/24 12:34:12 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

typedef enum e_philosophers_state {
	EATING,
	SLEEPING,
	THINKING
}	t_philosophers_state;

typedef enum e_fork_state {
	FREE,
	USED
}	t_fork_state;

typedef enum e_error_codes {
	INVALID_ARGUMENTS = 1,
}	t_error_codes;

typedef struct s_parameters {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
}	t_parameters;

typedef struct s_philosopher {
	int						id;
	t_philosophers_state	state;
	int						number_of_time_has_eaten;
	int						last_time_has_eaten;
}	t_philosopher;

typedef struct s_fork {
	int				id;
	t_fork_state	state;
}	t_fork;

#endif
