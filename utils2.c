/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:03:02 by llaurenc          #+#    #+#             */
/*   Updated: 2023/05/17 14:03:02 by llaurenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *ph, int i)
{
	pthread_mutex_lock(&ph->p_args->dead);
	if (i)
		ph->p_args->stop = i;
	if (ph->p_args->stop)
	{
		pthread_mutex_unlock(&ph->p_args->dead);
		return (1);
	}
	pthread_mutex_unlock(&ph->p_args->dead);
	return (0);
}

long int	actual_time(void)
{
	long int			time;
	struct timeval		current_time;

	time = 0;
	gettimeofday(&current_time, NULL);
	if (gettimeofday(&current_time, NULL) == -1)
		ft_exit("Gettimeofday returned -1\n");
	time = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (time);
}

void	ft_usleep(long int time_in_ms)
{
	long int	start_time;

	start_time = 0;
	start_time = actual_time();
	while ((actual_time() - start_time) < time_in_ms)
		usleep(time_in_ms / 10);
}

void	write_status(char *str, t_philo *ph)
{	
	long int	time;

	time = actual_time() - ph->p_args->start_time;
	printf("%.4ld %d %s\n", time, ph->id, str);
}
