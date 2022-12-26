#include "philo.h"

void	get_time(t_philo *philo)
{
	static int	ms;
	static int	start;

	pthread_mutex_lock(philo->action);
	gettimeofday(&philo->tv, NULL);
	ms = (philo->tv.tv_sec * 1000) + (philo->tv.tv_usec / 1000);
	if (start == 0)
		start = ms;
	philo->time = ms - start;
	pthread_mutex_unlock(philo->action);
}

void	*distribution(void *ptr)
{
	t_philo			*philo;

	philo = (t_philo *)ptr;
	philo->death = philo->time + philo->die;
	while (1)
	{
		check_death(philo);
		if ((philo->sim && philo->ate != 0) || (!philo->sim))
			p_eat(philo);
		if (philo->sim && philo->ate == 0)
			return (0);
		p_sleep(philo);
		if (!is_good(philo))
			return (0);
		p_think(philo);
		usleep(200);
	}
	return (0);
}

void	create_threads(t_philo *philo)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (++i < philo->philo_count)
	{
		if (i % 2 == 0)
		{
			pthread_create(&philo[i].thread, NULL, \
				distribution, (void *)&philo[i]);
		}
	}
	usleep(600);
	i = -1;
	while (++i < philo->philo_count)
	{
		if (i % 2 != 0)
		{
			pthread_create(&philo[i].thread, NULL, \
					distribution, (void *)&philo[i]);
		}
	}
	while (j < philo->philo_count)
		pthread_join(philo[j++].thread, NULL);
}

void	clean_up(t_philo *philo, pthread_mutex_t *mutexes, int *fork_arr)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(philo->action);
	while (i < philo->philo_count)
		pthread_mutex_destroy(&mutexes[i++]);
	free(philo->action);
	free(philo->status);
	free(mutexes);
	free(fork_arr);
	free(philo);
}

int	main(int argc, char **argv)
{	
	t_philo			*philo;
	pthread_mutex_t	*mutexes;
	int				*fork_arr;
	int				size;

	mutexes = NULL;
	if (argc == 5 || argc == 6)
	{
		if (check_args(argc, argv))
		{
			size = ft_atoi(argv[1]);
			philo = malloc(sizeof(t_philo) * size);
			if (!philo)
				return (0);
			set_args(philo, argc, argv);
			mutexes = init_mutexes(size);
			set_mutexes(philo, mutexes);
			fork_arr = forks(philo);
			create_threads(philo);
			clean_up(philo, mutexes, fork_arr);
		}
	}
	return (0);
}
