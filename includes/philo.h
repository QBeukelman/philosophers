

#ifndef 	PHILO_H
# define	PHILO_H

// ===== [ includes ] =====
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>


# ifndef NULL
#  define NULL ((char *)0)
# endif

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
	int					philo_nb;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					time_think;
	int					must_eat;
	int					done;
	int					died;
	pthread_mutex_t		*mutex;
}	t_data;

typedef struct	s_philo
{
	int					id;
	unsigned long		last_meal;
	int					meal_counter;
	int					l_fork;
	int					r_fork;
	t_data				*data;
	pthread_mutex_t		*fork;
}	t_philo;


// ===== [ init ] =====
int				ft_init(t_philo *philos_array, t_data *data, int argc, char *argv[]);
t_data			*ft_init_data(t_data *data, int argc, char *argv[]);
t_philo			*ft_init_philo(t_philo *philos_array, t_data *data);
t_data			*ft_init_data_mutexes(t_data *data);


// ===== [ check args ] =====
bool			ft_is_numberic(char *str);
int				ft_check_args(int argc, char *argv[]);


// ===== [ tools ] =====
long int		ft_atol(char *str);


// ===== [ sim utils ] =====
void			ft_print(t_philo *philos_array, char *str);


// ===== [ time utils ] =====
unsigned long	ft_abs_time(void);
unsigned long	ft_rel_time(unsigned long begin);
void			ft_msleep(unsigned long msec);


// ===== [ simulator ] =====
int				ft_simulator(t_philo *philos_array, t_data *data);
// static int		ft_monitor(t_philo *philos_array, t_data *data);


// ===== [ simulation ] =====
void			*ft_simulation(void *arg);


#endif
