/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doing.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurenc <llaurenc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:15:14 by llaurenc          #+#    #+#             */
/*   Updated: 2023/06/07 15:53:04 by llaurenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_eat(t_philo *ph)
{
	ft_usleep(ph->p_args->eat_time);
	ph->nb_eat++;
}

void	ft_dodo(t_philo *ph)
{
	pthread_mutex_lock(&ph->p_args->write_mutex);
	write_status("is sleeping", ph);
	pthread_mutex_unlock(&ph->p_args->write_mutex);
	ft_usleep(ph->p_args->sleep_time);
	pthread_mutex_lock(&ph->p_args->write_mutex);
	write_status("is thinking", ph);
	pthread_mutex_unlock(&ph->p_args->write_mutex);
}

void	ft_doing(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_f);
	pthread_mutex_lock(&ph->p_args->write_mutex);
	write_status("has taken a left fork", ph);
	pthread_mutex_unlock(&ph->p_args->write_mutex);
	pthread_mutex_lock(ph->r_f);
	pthread_mutex_lock(&ph->p_args->write_mutex);
	write_status("has taken a right fork", ph);
	pthread_mutex_unlock(&ph->p_args->write_mutex);
	pthread_mutex_lock(&ph->p_args->write_mutex);
	write_status("is eating", ph);
	pthread_mutex_lock(&ph->p_args->time_eat);
	ph->ms_eat = actual_time();
	pthread_mutex_unlock(&ph->p_args->time_eat);
	pthread_mutex_unlock(&ph->p_args->write_mutex);
	ft_eat(ph);
	pthread_mutex_unlock(ph->r_f);
	pthread_mutex_lock(&ph->p_args->write_mutex);
	write_status("lache la fourche right", ph);
	pthread_mutex_unlock(&ph->p_args->write_mutex);
	pthread_mutex_unlock(&ph->l_f);
	pthread_mutex_lock(&ph->p_args->write_mutex);
	write_status("lache la fourche left", ph);
	pthread_mutex_unlock(&ph->p_args->write_mutex);
	ft_dodo(ph);
}
