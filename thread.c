/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 13:41:01 by llaurenc          #+#    #+#             */
/*   Updated: 2023/10/17 16:11:26 by llaurenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*is_dead(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	ft_usleep(ph->p_args->die_time + 1);
	pthread_mutex_lock(&ph->p_args->time_eat);
	pthread_mutex_lock(&ph->p_args->finish);
	if (!(check_death(ph, 0)) && !ph->finish && ((actual_time() - ph->ms_eat) \
		>= (long)ph->p_args->die_time))
	{
		pthread_mutex_unlock(&ph->p_args->finish);
		pthread_mutex_unlock(&ph->p_args->time_eat);
		pthread_mutex_lock(&ph->p_args->write_mutex);
		write_status("is died", ph);
		exit(1);
		pthread_mutex_unlock(&ph->p_args->write_mutex);
		check_death(ph, 1);
	}
	pthread_mutex_unlock(&ph->p_args->finish);
	pthread_mutex_unlock(&ph->p_args->time_eat);
	return (NULL);
}

void	*p_thread(void *data)
{
	t_philo	*ph;

	ph = (t_philo *)data;
	if (ph->id % 2)
		ft_usleep(ph->p_args->eat_time / 10);
	while (!check_death(ph, 0))
	{
		pthread_create(&(ph->thread_death_id), NULL, is_dead, data);
		ft_doing(ph);
		pthread_detach(ph->thread_death_id);
		if (ph->nb_eat == ph->p_args->meal_eat)
		{
			ph->finish = 1;
			ph->p_args->nb_p_end++;
			if (ph->p_args->nb_p_end == ph->p_args->number)
			{
				check_death(ph, 2);
			}
			return (NULL);
		}
	}
	return (NULL);
}

int	init_threading(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->args.number)
	{
		if (pthread_create(&(p->ph[i].thread_id), NULL, p_thread, &p->ph[i]))
			ft_exit("pthread ne retourne pas 0\n");
		i++;
	}
	return (1);
}
