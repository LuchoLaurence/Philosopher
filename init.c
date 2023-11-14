/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 13:01:35 by llaurenc          #+#    #+#             */
/*   Updated: 2023/05/22 13:01:35 by llaurenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_p *p)
{
	pthread_mutex_init(&p->args.write_mutex, NULL);
	pthread_mutex_init(&p->args.dead, NULL);
	pthread_mutex_init(&p->args.time_eat, NULL);
	pthread_mutex_init(&p->args.finish, NULL);
}

void	init_philosophers(t_p *p)
{
	int	i;

	i = 0;
	while (i < p->args.number)
	{
		p->ph[i].id = i + 1;
		p->ph[i].ms_eat = p->args.start_time;
		p->ph[i].nb_eat = 0;
		p->ph[i].finish = 0;
		p->ph[i].r_f = NULL;
		pthread_mutex_init(&p->ph[i].l_f, NULL);
		p->ph[i].p_args = &p->args;
		if (p->args.number == 1)
			ft_exit("il ne peut pas y avoir qu'un philosophe");
		if (i == p->args.number - 1)
			p->ph[i].r_f = &p->ph[0].l_f;
		else
			p->ph[i].r_f = &p->ph[i + 1].l_f;
		i++;
	}
}

int	init(t_p *p)
{
	p->args.start_time = actual_time();
	p->args.stop = 0;
	p->args.nb_p_end = 0;
	init_mutex(p);
	init_philosophers(p);
	return (1);
}
