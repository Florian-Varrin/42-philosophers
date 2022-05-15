/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 15:02:58 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/10 17:37:14 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>

# define WAIT_FREQ 50

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
	ERROR_WHILE_CREATING_MUTEX = 3,
	ERROR_WHILE_CREATING_THREAD = 4
}	t_error_codes;

typedef struct s_parameters {
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_must_eat;
}	t_parameters;

typedef struct s_philosopher {
	int						id;
	t_philosophers_state	state;
	int						number_of_time_has_eaten;
	long					last_time_has_eaten;
	_Bool					is_dead;
}	t_philosopher;

typedef struct s_fork {
	int				id;
	t_fork_state	state;
}	t_fork;

typedef struct s_state {
	t_parameters	*parameters;
	t_philosopher	**philosophers;
	t_fork			**forks;
	pthread_mutex_t	forks_mutex;
	long			start_time;
}	t_state;

typedef struct s_life_cycle_state {
	int		id;
	t_state	*state;
}	t_life_cycle_state;

/* Utils */

/**
 * Transform a string to an int
 *
 * @param {char *} str
 *
 * @return {int}
 */
int					ft_atoi(const char *str);

/**
 * @param {char *} str
 *
 * @return {int} length of a string
 */
int					ft_strlen(const char *str);

/**
 * Return current timestamp is ms
 *
 * @return {long} timestamp
 */

int					exit_error(int exit_code, char *message);

void				log_message(t_state *state, int id, char *message);

/* Time */

long				get_current_time(void);

void				wait_ms(int ms);

/* State */
int					init_state(t_state **state, int argc, char **argv);

t_state				*destroy_state(t_state *state);

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
int					parse_parameters(
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
_Bool				check_parameters_constraints(t_parameters *parameters);

/* Philosophers */
int					init_philosophers(t_state *state, t_parameters *parameters);

void				destroy_philosophers(t_state *state);

t_philosopher		*get_philosopher_from_id(
						t_philosopher **philosophers, int id);

t_life_cycle_state	**init_philosopher_states(t_state *state);

t_life_cycle_state	*destroy_philosopher_states(
		t_life_cycle_state **philosopher_states);

t_fork				**set_needed_forks(t_fork **forks, t_state *state, int philosopher_id);

_Bool				check_if_is_dead(t_state *state, int philosopher_id);

void				philosopher_eat(t_state *state, t_philosopher *philosopher);

void				philosopher_sleep(t_state *state, t_philosopher *philosopher);

void				philosopher_die(t_state *state, t_philosopher *philosopher);

void				*run_life_cycle(void *philosopher_state);

_Bool				check_if_a_philosopher_is_dead(t_state *state);

_Bool				check_if_all_have_eaten_enough(t_state *state);

/* Forks */
int					init_forks(t_state *state, t_parameters *parameters);

void				destroy_forks(t_state *state);

/* Threads */
pthread_t			*init_threads(t_state *state);

pthread_t			*destroy_threads(pthread_t *threads);

int					create_threads(t_state *state, pthread_t *threads,
									  t_life_cycle_state **philosopher_states);
#endif
