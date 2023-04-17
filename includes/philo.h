/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   philo.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: qbeukelm <qbeukelm@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/03 10:54:13 by qbeukelm      #+#    #+#                 */
/*   Updated: 2023/04/17 09:42:27 by qbeukelm      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

// ===== [ includes ] =====
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>

// ===== [ enums ] =====
typedef enum e_mutexes
{
	PRINT,
	MEALS,
	DONE,
	DIED,
	M_NUM
}	t_mutexes;

typedef enum e_exit
{
	SUCCESS,
	FAILURE
}	t_exit;

typedef enum e_bool
{
	FALSE,
	TRUE
}	t_bool;

// ===== [ struct ] =====
typedef struct s_data
{
	unsigned long		sim_begin;
	unsigned char		philo_nb;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					time_think;
	int					must_eat;
	unsigned char		done;
	unsigned char		died;
	unsigned char		id_died;
	unsigned long		time_of_death;
	pthread_mutex_t		*mutex;
}	t_data;

typedef struct s_philo
{
	int					id;
	unsigned long		last_meal;
	int					meal_counter;
	unsigned char		l_fork;
	unsigned char		r_fork;
	t_data				*data;
	pthread_mutex_t		*fork;
}	t_philo;

//====================================================================: Init
// ===== [ init ] =====
int				ft_init(t_philo **p_a, t_data **data, int argc, char *argv[]);
int				ft_init_helper(t_philo **p_a, t_data *data, pthread_mutex_t *f);
int				ft_init_data(t_data **data, int argc, char *argv[]);
int				ft_init_philo(t_philo **philos_array, t_data *data);
int				ft_init_data_mutexes(t_data **data);

// ===== [ check args ] =====
bool			ft_is_numberic(char *str);
int				ft_check_args(int argc, char *argv[]);
int				ft_check_args_helper(int argc, char *argv[]);
void			ft_one_philo(char *argv[]);

//====================================================================: Tools
// ===== [ tools ] =====
long int		ft_atol(char *str);

// ===== [ print utils ] =====
void			ft_print(t_philo *philos_array, char *str);
void			ft_printf_all_done(t_philo *self);
void			ft_printf_died(t_data *data);
void			ft_print_error(char *str);

// ===== [ time utils ] =====
unsigned long	ft_abs_time(void);
unsigned long	ft_rel_time(unsigned long begin);
void			ft_msleep(unsigned long msec);

//====================================================================: Sim
// ===== [ simulator ] =====
int				ft_simulator(t_philo *philos_array, t_data *data);
int				ft_create_threads(t_philo *p_a, t_data *data, pthread_t *th);
void			ft_end_conditions(t_philo *philos_array, t_data *data);

//====================================================================: Thread
// ===== [ simulation thread ] =====
void			*ft_sim_thread(void *arg);
int				ft_observe_thread(t_philo *philos_array, t_data *data);
int				ft_sleep(t_philo *self);
int				ft_think(t_philo *self);

// ===== [ end conditions ] =====
void			ft_died(t_philo *philos_array, t_data *data);
int				ft_check_die(t_philo *self);

// ===== [ done conditions ] =====
int				ft_all_done(t_philo *p_a, t_data *data);
int				ft_is_done(t_philo *self);
void			ft_done(t_data *data);
int				ft_max(int a, int b);
int				ft_min(int a, int b);

// ===== [ eating ] =====
int				ft_eating(t_philo *self);
int				ft_start_eating(t_philo *self);
int				ft_finish_eating(t_philo *self);

//====================================================================: Exit
// ===== [ clean exit ] =====
void			ft_destroy_mutexes(t_philo *philo, t_data *data);
void			ft_free_structs(t_philo *philos_array, t_data *data);
void			ft_exit(t_philo *philos_array, t_data *data, pthread_t *th);
int				ft_exit_init(t_philo **philos_array, t_data **data);

#endif
