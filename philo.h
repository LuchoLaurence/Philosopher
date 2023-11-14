/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llaurenc <llaurenc@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 14:08:06 by llaurenc          #+#    #+#             */
/*   Updated: 2023/05/15 15:41:41 by llaurenc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_arg
{
	int				number;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				meal_eat;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	dead;
	pthread_mutex_t	time_eat;
	pthread_mutex_t	finish;
	long int		start_time;
	int				nb_p_end;
	int				stop;
}	t_arg;
typedef struct s_philo
{
	int					id;
	long int			ms_eat;
	int					nb_eat;
	int					finish;
	pthread_mutex_t		*r_f;
	pthread_mutex_t		l_f;
	pthread_t			thread_id;
	pthread_t			thread_death_id;
	t_arg				*p_args;
}	t_philo;

typedef struct s_p
{
	t_philo	*ph;
	t_arg	args;

}	t_p;

void		ft_exit(char *str);
int			check_state(t_p *p);
void		ft_stop(t_p *p);

int			check_args(int argc, char **argv, t_p *p);
int			is_numeric(char **argv, int i, int j);

int			ft_atoi(char *str);
int			ft_strlen(char *str);

int			check_death(t_philo *ph, int i);
long int	actual_time(void);
void		ft_usleep(long int time_in_ms);
void		write_status(char *str, t_philo *ph);

int			init(t_p *p);
void		init_mutex(t_p *p);

int			init_threading(t_p *p);

void		ft_eat(t_philo *ph);
void		ft_doing(t_philo *ph);
void		ft_dodo(t_philo *ph);
#endif