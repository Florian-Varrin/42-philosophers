/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By:  <>                                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 16:05:45 by                   #+#    #+#             */
/*   Updated: 2022/04/24 14:57:52 by fvarrin          ###   ########.fr       */
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
	ERROR_WHILE_ALLOCATING_MEMORY = 2,
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

typedef struct s_state {
	t_parameters	*parameters;
	t_philosopher	**philosophers;
	t_fork			**forks;
}	t_state;

/* Utils */

/**
 * Transform a string to an int
 *
 * @param {char *} str
 *
 * @return {int}
 */
int				ft_atoi(const char *str);

/**
 * @param {char *} str
 *
 * @return {int} length of a string
 */
int				ft_strlen(const char *str);

/* State */
int				init_state(t_state **state, int argc, char **argv);

t_state			*destroy_state(t_state *state);

/* Parameters */
/**
 * Parse and init parameters whit arguments.
 * Return 0 if success or error code otherwise
 *
 * @param {t_parameters *} parameters
 * @param {int} argc
 * @param {char *} argv
 *
 * @return {int} result
 */
int				parse_parameters(
					t_parameters **parameters,
					int argc,
					char **argv
					);

/**
 * Check that parameters respect constraints. Return true if it's ok, false
 * if the parameters are illegal.
 *
 * @param {t_parameters *} parameters
 * @return  {_Bool} result
 */
_Bool			check_parameters_constraints(t_parameters *parameters);

/* Philosophers */
int				init_philosophers(t_state *state, t_parameters *parameters);

void			destroy_philosophers(t_state *state);

/* Forks */
int				init_forks(t_state *state, t_parameters *parameters);

void			destroy_forks(t_state *state);
#endif
