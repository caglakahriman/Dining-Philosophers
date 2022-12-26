#include "philo.h"

void	p_kill(t_philo *philo)
{
	pthread_mutex_lock(philo->action);
	if (*philo->status == 1)
	{
		*philo->status = 0;
		printf("%lu %d died\n", philo->time, philo->id);
	}
	pthread_mutex_unlock(philo->action);
}

int	is_good(t_philo *philo)
{
	int	value;

	pthread_mutex_lock(philo->action);
	value = *philo->status;
	pthread_mutex_unlock(philo->action);
	return (value);
}

void	check_death(t_philo *philo)
{
	get_time(philo);
	if (philo->time >= philo->death && is_good(philo))
		p_kill(philo);
}
