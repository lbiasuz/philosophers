/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz@student.42sp.org.br <lbiasuz>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 22:29:44 by lbiasuz@stu       #+#    #+#             */
/*   Updated: 2023/09/20 22:23:27 by lbiasuz@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	allowed_input(int argc, char **argv)
{
	(void)argv;
	if (argc > 6 || argc < 5)
	{
		write(2, USAGE, sizeof(USAGE) - 1);
		return (0);
	}
	return (1);
}

t_ph	*init_sim(t_st *settings, t_ph *philosophers)
{
	int		i;

	i = 0;
	while (i < settings->nop)
	{
		philosophers[i].id = i;
		philosophers[i].lasteaten = 0;
		philosophers[i].fork[0] = &settings->forks[i];
		philosophers[i].fork[1] = &settings->forks[i + 1];
		philosophers[i].lock = (pthread_mutex_t *)ft_calloc(
				1, sizeof(pthread_mutex_t));
		philosophers[i].st = settings;
		i++;
	}
	philosophers[i - 1].fork[0] = &settings->forks[i - 1];
	philosophers[i - 1].fork[1] = &settings->forks[0];
	settings->start_time = tv2ul(get_temp());
	while (--i >= 0)
		pthread_create(&settings->philosophers[i], NULL,
			philosopher_lifecycle, (void *)&philosophers[i]);
	return (philosophers);
}

t_st	*init_settings(char **args, int argc, t_st *st)
{
	t_tv	start;

	st->nop = ft_atol(args[1]);
	st->die_lap = ft_atol(args[2]);
	st->eat_lap = ft_atol(args[3]);
	st->sleep_lap = ft_atol(args[4]);
	if (argc == 6)
		st->servings = ft_atol(args[5]);
	else
		st->servings = -1;
	st->its_over = 0;
	st->satisfied = 0;
	gettimeofday(&start, NULL);
	st->start_time = tv2ul(start);
	st->forks = ft_calloc(st->nop, sizeof(pthread_mutex_t));
	st->philosophers = (pthread_t *)ft_calloc(st->nop, sizeof(pthread_t));
	st->lock = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(st->lock, NULL);
	return (st);
}
