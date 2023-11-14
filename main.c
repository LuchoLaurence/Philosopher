/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurenc <llaurenc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:07:35 by llaurenc          #+#    #+#             */
/*   Updated: 2023/05/15 15:46:29 by llaurenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_exit(char *str)
{
	printf("Erreur :\n");
	printf("%s", str);
	exit(1);
}

int	check_state(t_p *p)
{
	if (p->args.stop)
		return (1);
	return (0);
}

void	ft_stop(t_p *p)
{
	int	i;

	i = -1;
	while (!check_state(p))
		ft_usleep(1);
	while (++i < p->args.number)
		pthread_join(p->ph[i].thread_id, NULL);
	pthread_mutex_destroy(&p->args.write_mutex);
	i = -1;
	while (++i < p->args.number)
		pthread_mutex_destroy(&p->ph[i].l_f);
	if (p->args.stop == 2)
		printf("Each philosopher ate %d time(s)\n", p->args.meal_eat);
	free(p->ph);

}

int	main(int argc, char **argv)
{
	t_p	p;

	if (!(check_args(argc, argv, &p)))
		ft_exit("Arguments invalides");
	p.ph = malloc(sizeof(t_philo) * p.args.number);
	if (!p.ph)
		ft_exit("Malloc returned NULL");
	if (!init(&p) || !init_threading(&p))
	{
		free(p.ph);
		return (0);
	}
	ft_stop(&p);
	return (0);
}
