#include "philo.h"

int	*forks(t_philo *philo)
{
	int	i;
	int	j;
	int	*forks;

	i = -1;
	j = 0;
	forks = malloc(sizeof(int) * philo->philo_count);
	if (!forks)
		return (0);
	while (++i < philo->philo_count)
		forks[i] = 1;
	i = 0;
	philo[i].rfork = &forks[philo->philo_count - 1];
	philo[i].lfork = &forks[j];
	i++;
	while (i < philo->philo_count)
	{
		philo[i].rfork = &forks[j++];
		philo[i++].lfork = &forks[j];
	}
	return (forks);
}

void	take_fork(t_philo *philo)
{
	while (1)
	{
		check_death(philo);
		if (!is_good(philo))
			return ;
		pthread_mutex_lock(philo->rmutex);
		if (*philo->rfork && is_good(philo))
		{
			philo->rhand = 1;
			*philo->rfork = 0;
			printf("%lu %d has taken a fork\n", philo->time, philo->id);
		}
		pthread_mutex_unlock(philo->rmutex);
		pthread_mutex_lock(philo->lmutex);
		if (*philo->lfork && is_good(philo))
		{
			philo->lhand = 1;
			*philo->lfork = 0;
			printf("%lu %d has taken a fork\n", philo->time, philo->id);
		}
		pthread_mutex_unlock(philo->lmutex);
		if (philo->lhand && philo->rhand)
			break ;
		usleep(200);
	}
}

void	leave_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->lmutex);
	if (*philo->lfork == 0)
	{
		philo->lhand = 0;
		*philo->lfork = 1;
	}
	pthread_mutex_unlock(philo->lmutex);
	pthread_mutex_lock(philo->rmutex);
	if (*philo->rfork == 0)
	{
		philo->rhand = 0;
		*philo->rfork = 1;
	}
	pthread_mutex_unlock(philo->rmutex);
	if (!philo->lhand && !philo->rhand)
		return ;
}
