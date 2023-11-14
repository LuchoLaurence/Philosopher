/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurenc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 09:59:26 by llaurenc          #+#    #+#             */
/*   Updated: 2023/05/17 09:59:26 by llaurenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv, t_p *p)
{
	if ((argc == 5 || argc == 6) && is_numeric(argv, 0, 1))
	{
		p->args.number = ft_atoi(argv[1]);
		p->args. die_time = ft_atoi(argv[2]);
		p->args.eat_time = ft_atoi(argv[3]);
		p->args.sleep_time = ft_atoi(argv[4]);
		p->args.meal_eat = -1;
		if (argc == 6)
			p->args.meal_eat = ft_atoi(argv[5]);
		if (p->args.number <= 0 || p->args.die_time <= 0
			|| p->args.eat_time <= 0 || p->args.sleep_time <= 0)
			ft_exit("Args must be positive");
		return (1);
	}
	return (0);
}

int	is_numeric(char **argv, int i, int j)
{
	while (argv[j])
	{
		i = 0;
		while (argv[j][i])
		{
			if (argv[j][i] < '0' || argv[j][i] > '9')
				ft_exit("Args must be positive integers");
			if (ft_strlen(argv[j]) > 10)
				ft_exit("Args must be lower than 10 000 000 000");
			i++;
		}
		j++;
	}
	return (1);
}
