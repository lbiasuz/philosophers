/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:37:26 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/08/30 22:03:55 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	allowed_input(int argc, char **argv)
{
	(void)argv;
	if (argc > 6 || argc < 5)
	{
		write(2, USAGE, sizeof(USAGE) - 1);
		return (0);
	}
	return (1);
}

int		philosopher_lifecycle(t_st *st, t_ph *ph)
{	
	t_tv	temp;

	printf("%ld philosopher %d has taken a fork", gettimeofday(&temp, NULL), ph->id);
	pthread_mutex_lock(ph->fork[0]);
	printf("philosopher %d has taken a fork", ph->id);
	pthread_mutex_lock(ph->fork[1]);
	printf("philosopher %d is eating");
	usleep(st->sleep_lap);
}

t_ph	*init_sim(t_st *settings)
{
	int		i;
	t_ph	*philosophers;

	i = 0;
	philosophers = (t_ph *) ft_calloc(settings->nop, sizeof(t_ph));
	while (i < settings->nop)
	{
		philosophers[i].id = i;
		philosophers[i].is_eating = 0;
		philosophers[i].is_sleeping = 0;
		philosophers[i].lasteaten = 0;
		philosophers[i].fork[0] = &settings->forks[i];
		philosophers[i].fork[1] = &settings->forks[i + 1];
		i++;
	}
	philosophers[i].id = i;
	philosophers[settings->nop].is_eating = 0;
	philosophers[settings->nop].is_sleeping = 0;
	philosophers[settings->nop].fork[0] = &settings->forks[settings->nop - 1];
	philosophers[settings->nop].fork[1] = &settings->forks[0];
	while (--i >= 0)
		pthread_create(&settings->philosophers[i], NULL, philosopher_lifecycle, (void *) &philosophers[i]);
	return (philosophers);
}

t_st	*init_settings(char **args, int argc)
{
	t_st	*settings;
	t_tv	start;

	settings = ft_calloc(1, sizeof(t_st));
	settings->nop = ft_atol(args[1]);
	settings->die_lap = ft_atol(args[2]);
	settings->eat_lap = ft_atol(args[3]);
	settings->sleep_lap = ft_atol(args[4]);
	if (argc == 6)
		settings->servings = ft_atol(args[5]);
	else
		settings->servings = -1;
	settings->its_over = 0;
	gettimeofday(&start, NULL);
	settings->start_time = timeval_to_ul(start);
	settings->forks = ft_calloc(settings->nop, sizeof(pthread_mutex_t));
	return (settings);
}

int	main(int argc, char **argv)
{
	t_st	*settings;

	if (!allowed_input(argc, argv))
		return (1);
	settings = init_settings(argv, argc);
	if (settings->nop == 0)
		return (1);
	else if (settings->nop == 1)
		return (single_philo_exec());
	
	init_sim(settings);
}
// (pthread_mutex_t **) ft_calloc(settings->nop, sizeof(pthread_mutex_t));