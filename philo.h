#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				*status;
	int				*lfork;
	int				*rfork;
	int				philo_count;
	int				lhand;
	int				rhand;
	int				sim;
	int				ate;
	int				id;
	pthread_mutex_t	*lmutex;
	pthread_mutex_t	*rmutex;
	pthread_mutex_t	*action;
	pthread_t		thread;
	unsigned long	time;
	unsigned long	last_ate;
	unsigned long	last_sleep;
	unsigned long	die;
	unsigned long	sleep;
	unsigned long	eat;
	unsigned long	death;
	struct timeval	tv;
}				t_philo;

pthread_mutex_t	*init_mutexes(int size);
void			set_mutexes(t_philo *philo, pthread_mutex_t *mutexes);
void			set_args(t_philo *philo, int argc, char **argv);
void			print_message(t_philo *philo, char *str);
void			leave_forks(t_philo *philo);
void			check_death(t_philo *philo);
void			take_fork(t_philo *philo);
void			take_fork(t_philo *philo);
void			get_time(t_philo *philo);
void			p_sleep(t_philo *philo);
void			p_think(t_philo *philo);
void			p_kill(t_philo *philo);
void			p_eat(t_philo *philo);
void			p_die(t_philo *philo);
int				check_args(int argc, char **argv);
int				is_good(t_philo *philo);
int				*forks(t_philo *philo);
unsigned long	ft_atoi(const char *str);
#endif
