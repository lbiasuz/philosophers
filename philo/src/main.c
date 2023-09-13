/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz@student.42sp.org.br <lbiasuz>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:37:26 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/09/13 08:54:52 by lbiasuz@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*philosopher_lifecycle(void *arg)
{
	t_ph	*ph;
	t_tv	temp;

	ph = (t_ph *)arg;
	pthread_mutex_lock(ph->st->lock);
	while (!ph->st->its_over)
	{
		pthread_mutex_unlock(ph->st->lock);

		if (ph->id % 2 == 0)
		{
			pthread_mutex_lock(ph->fork[0]);
			log_action(ph, "has taken a fork");
			pthread_mutex_lock(ph->fork[1]);
		}
		else
		{
			pthread_mutex_lock(ph->fork[1]);
			log_action(ph, "has taken a fork");
			pthread_mutex_lock(ph->fork[0]);
		}
		log_action(ph, "has taken a fork");

		pthread_mutex_lock(ph->lock);
		gettimeofday(&temp, NULL);
		ph->lasteaten = tv2ul(temp);
		ph->times_eaten++;
		pthread_mutex_unlock(ph->lock);

		log_action(ph, "is eating");
		usleep(ph->st->eat_lap * 1000);

		pthread_mutex_unlock(ph->fork[0]);
		pthread_mutex_unlock(ph->fork[1]);

		log_action(ph, "is sleeping");
		usleep(ph->st->sleep_lap * 1000);

		log_action(ph, "is thinking");
		pthread_mutex_lock(ph->st->lock);
	}
	pthread_mutex_unlock(ph->st->lock);
	return (NULL);
}

t_ph	*init_sim(t_st *settings, t_ph *philosophers)
{
	int		i;
	t_tv	temp;

	i = 0;
	while (i < settings->nop)
	{
		philosophers[i].id = i;
		philosophers[i].is_eating = 0;
		philosophers[i].is_sleeping = 0;
		philosophers[i].lasteaten = 0;
		philosophers[i].fork[0] = &settings->forks[i];
		philosophers[i].fork[1] = &settings->forks[i + 1];
		philosophers[i].lock = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
		philosophers[i].st = settings;
		i++;
	}
	philosophers[i].fork[0] = &settings->forks[i];
	philosophers[i].fork[1] = &settings->forks[0];
	gettimeofday(&temp, NULL);
	settings->start_time = tv2ul(temp);
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
	gettimeofday(&start, NULL);
	st->start_time = tv2ul(start);
	st->forks = ft_calloc(st->nop, sizeof(pthread_mutex_t));
	st->philosophers = (pthread_t *)ft_calloc(st->nop, sizeof(pthread_t));
	st->lock = (pthread_mutex_t *)ft_calloc(1, sizeof(pthread_mutex_t));
	pthread_mutex_init(st->lock, NULL);
	return (st);
}

void	watch(t_ph *philosophers)
{
	t_tv	temp;
	t_st	*st;
	int		id;

	id = -1;
	st = philosophers[0].st;
	while (1)
	{
		if (id < st->nop - 1)
			id++;
		else
			id = 0;
		pthread_mutex_lock(philosophers[id].lock);
		gettimeofday(&temp, NULL);
		if (tv2ul(temp) - st->start_time > philosophers[id].lasteaten && (tv2ul(temp) - st->start_time - philosophers[id].lasteaten) > st->die_lap)
		{
			pthread_mutex_lock(st->lock);
			st->its_over = 1;
			pthread_mutex_unlock(st->lock);
			printf("%ld philosopher %d %s\n",
				(tv2ul(temp) - st->start_time), id, "died");
			pthread_mutex_unlock(philosophers[id].lock);
			break ;
		}
		pthread_mutex_unlock(philosophers[id].lock);
	}
	id = st->nop;
	while (id > 0)
	{
		pthread_join(st->philosophers[id], NULL);
		id--;
	}
}

int	main(int argc, char **argv)
{
	t_st	*settings;
	t_ph	*philosophers;

	if (!allowed_input(argc, argv))
		return (1);
	settings = (t_st *)ft_calloc(1, sizeof(t_st));
	settings = init_settings(argv, argc, settings);
	philosophers = (t_ph *)ft_calloc(settings->nop, sizeof(t_ph));
	init_sim(settings, philosophers);
	watch(philosophers);
	return (0);
}
