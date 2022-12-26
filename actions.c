#include "philo.h"

void	p_think(t_philo *philo)
{
	if (is_good(philo))
	{
		printf("%lu %d is thinking\n", philo->time, philo->id);
		usleep(200);
	}
}

void	p_sleep(t_philo *philo)
{
	if (is_good(philo))
	{
		philo->last_sleep = philo->time + philo->sleep;
		get_time(philo);
		printf("%lu %d is sleeping\n", philo->time, philo->id);
		while (philo->time <= philo->last_sleep && is_good(philo))
		{
			usleep(200);
			check_death(philo);
			get_time(philo);
			if (!is_good(philo))
				return ;
		}
	}
}

void	p_eat(t_philo *philo)
{
	take_fork(philo);
	if (is_good(philo))
	{
		printf("%lu %d is eating\n", philo->time, philo->id);
		philo->ate--;
		philo->last_ate = philo->time + philo->eat;
		philo->death = philo->time + philo->die;
		while (philo->time <= philo->last_ate && is_good(philo))
		{
			usleep(200);
			if (!is_good(philo))
				return ;
			get_time(philo);
		}
		leave_forks(philo);
	}
}
