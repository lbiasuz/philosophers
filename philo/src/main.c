/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz@student.42sp.org.br <lbiasuz>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:37:26 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/09/05 22:34:21 by lbiasuz@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*philosopher_lifecycle(void *arg)
{
	t_ph	*ph;
	t_tv	temp;

	ph = (t_ph *) arg;
	log_action(ph, "has taken a fork");
	pthread_mutex_lock(ph->fork[0]);
	log_action(ph, "has taken a fork");
	pthread_mutex_lock(ph->fork[1]);
	log_action(ph, "is eating");
	usleep(ph->st->eat_lap);
	log_action(ph, "is thinking");
	pthread_mutex_lock(ph->lock);
	gettimeofday(&temp, NULL);
	ph->lasteaten = tv2ul(temp);
	ph->times_eaten++;
	pthread_mutex_unlock(ph->lock);
	log_action(ph, "is thinking");
	return (NULL);
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
	philosophers[settings->nop].st = settings;
	while (--i >= 0)
		pthread_create(&settings->philosophers[i], NULL,
			philosopher_lifecycle, (void *) &philosophers[i]);
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
	settings->start_time = tv2ul(start);
	settings->forks = ft_calloc(settings->nop, sizeof(pthread_mutex_t));
	return (settings);
}

void	watch(t_ph	*philosophers)
{
	t_tv	temp;
	t_st	*st;
	int		id;

	id = -1;
	st = philosophers[0].st;
	while (1)
	{
		if (id < st->nop)
			id++;
		else
			id = 0;
		pthread_mutex_lock(philosophers[id].lock);
		gettimeofday(&temp, NULL);
		if ((tv2ul(temp) - philosophers[id].lasteaten) > st->die_lap)
		{
			pthread_mutex_lock(st->lock);
			st->its_over = 1;
			pthread_mutex_unlock(st->lock);
			break ;
		}
		pthread_mutex_unlock(philosophers[id].lock);
	}
}

int	main(int argc, char **argv)
{
	t_st	*settings;
	t_ph	*philosophers;

	if (!allowed_input(argc, argv))
		return (1);
	settings = init_settings(argv, argc);
	philosophers = init_sim(settings);
	watch(philosophers);
	return (0);
}
