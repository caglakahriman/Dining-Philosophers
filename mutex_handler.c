#include "philo.h"

pthread_mutex_t	*init_mutexes(int size)
{
	pthread_mutex_t	*mutexes;
	int				i;

	i = 0;
	mutexes = malloc(sizeof(pthread_mutex_t) * size);
	if (!mutexes)
		return (0);
	while (i < size)
	{
		pthread_mutex_init(&mutexes[i], NULL);
		i++;
	}
	return (mutexes);
}

void	set_mutexes(t_philo *philo, pthread_mutex_t *mutexes)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	philo[i].rmutex = &mutexes[philo->philo_count - 1];
	philo[i].lmutex = &mutexes[j];
	i++;
	while (i < philo->philo_count)
	{
		philo[i].rmutex = &mutexes[j++];
		philo[i++].lmutex = &mutexes[j];
	}
}
