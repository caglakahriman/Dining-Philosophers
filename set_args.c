#include "philo.h"

unsigned long	ft_atoi(const char *str)
{
	unsigned long	num;

	num = 0;
	while (*str)
		num = (num * 10) + (*str++ - 48);
	return (num);
}

int	check_args(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc - 1)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	set_basics(t_philo *philo, char **argv, \
		int *status, pthread_mutex_t *action)
{
	unsigned long	i;

	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		philo[i].die = ft_atoi(argv[2]);
		philo[i].eat = ft_atoi(argv[3]);
		philo[i].sleep = ft_atoi(argv[4]);
		philo[i].status = status;
		philo[i].action = action;
		i++;
	}
}

void	set_args(t_philo *philo, int argc, char **argv)
{
	unsigned long	i;
	int				*status;
	pthread_mutex_t	*action;

	i = 0;
	status = malloc(sizeof(int));
	action = malloc(sizeof(pthread_mutex_t));
	*status = 1;
	pthread_mutex_init(action, NULL);
	set_basics(philo, argv, status, action);
	while (i < ft_atoi(argv[1]))
	{
		philo[i].id = i + 1;
		philo[i].last_ate = 0;
		philo[i].lhand = 0;
		philo[i].rhand = 0;
		philo[i].philo_count = ft_atoi(argv[1]);
		if (argc == 6)
		{
			philo[i].sim = 1;
			philo[i].ate = ft_atoi(argv[5]);
		}
		i++;
	}
}
