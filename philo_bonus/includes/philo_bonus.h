/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvarrin <florian.varrin@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 13:48:03 by fvarrin           #+#    #+#             */
/*   Updated: 2022/05/29 12:22:30 by fvarrin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <semaphore.h>

# define WAIT_FREQ 50

# define FORKS_SEM_NAME "/forks"
# define SIM_END_SEM_NAME "/simEnd"
# define EATEN_ENOUGH_SEM_NAME "/allHaveEatenEnough"
# define CAN_WRITE_SEM_NAME "/canWrite"

typedef enum e_philosophers_state {
	EATING,
	SLEEPING,
	THINKING
}	t_philosophers_state;

typedef enum e_error_codes {
	INVALID_ARGUMENTS = 1,
	ERROR_WHILE_ALLOCATING_MEMORY = 2,
	ERROR_WHILE_FORKING_PROCESS = 3,
	ERROR_WHILE_CREATING_THREAD = 4,
	ERROR_WHILE_OPENING_SEMAPHORE = 5
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

typedef struct s_state
{
	t_parameters	*parameters;
	t_philosopher	*philosopher;
	sem_t			*forks;
	sem_t			*simulation_end;
	sem_t			*number_have_eaten_enough;
	sem_t			*can_write;
	long			start_time;
	int				*pids;
}	t_state;

/* Utils */

int				ft_strlen(const char *str);

int				ft_atoi(const char *str);

void			log_message(t_state *state, char *message, _Bool release_sem);

/* State */
int				init_state(t_state **state, int argc, char **argv);

t_state			*destroy_state(t_state *state);

/* Parameters */
int				parse_parameters(t_parameters **parameters, int argc,
					char **argv);

/* Time */
long			get_current_time(void);

void			wait_ms(int ms);

/* Philosopher */
int				init_philosophers(t_state *state);

t_philosopher	*destroy_philosopher(t_philosopher *philosopher);

void			philosopher_eat(t_state *state);

void			philosopher_sleep(t_state *state);

void			philosopher_die(t_state *state);

/* Forks */

void			take_forks(t_state *state);

void			let_forks_go(t_state *state);

/* Semaphores */
void			unlink_semaphores(void);

void			create_semaphores(t_state *state);

void			open_semaphores(t_state *state);

void			destroy_semaphores(t_state *state);

/* Life Cycle */
void			*run_life_cycle(t_state *state);

void			*check_all_have_eaten_enough(void *state_arg);
#endif