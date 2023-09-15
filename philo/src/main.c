/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz@student.42sp.org.br <lbiasuz>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:37:26 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/09/14 21:55:59 by lbiasuz@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	lock_forks(t_ph *ph, int a, int b)
{
	pthread_mutex_lock(ph->fork[a]);
	log_action(ph, "has taken a fork");
	pthread_mutex_lock(ph->fork[b]);
	log_action(ph, "has taken a fork");
}

t_tv	get_temp(void)
{
	t_tv	temp;

	gettimeofday(&temp, NULL);
	return (temp);
}

void	*philosopher_lifecycle(void *arg)
{
	pthread_mutex_lock(((t_ph *)arg)->st->lock);
	while (!((t_ph *)arg)->st->its_over)
	{
		pthread_mutex_unlock(((t_ph *)arg)->st->lock);
		if (((t_ph *)arg)->id % 2 == 0)
			lock_forks(((t_ph *)arg), 0, 1);
		else
			lock_forks(((t_ph *)arg), 1, 0);
		log_action(((t_ph *)arg), "has taken a fork");
		pthread_mutex_lock(((t_ph *)arg)->lock);
		((t_ph *)arg)->lasteaten = tv2ul(get_temp());
		((t_ph *)arg)->times_eaten++;
		pthread_mutex_unlock(((t_ph *)arg)->lock);
		log_action(((t_ph *)arg), "is eating");
		usleep(((t_ph *)arg)->st->eat_lap * 1000);
		pthread_mutex_unlock(((t_ph *)arg)->fork[0]);
		pthread_mutex_unlock(((t_ph *)arg)->fork[1]);
		log_action(((t_ph *)arg), "is sleeping");
		usleep(((t_ph *)arg)->st->sleep_lap * 1000);
		log_action(((t_ph *)arg), "is thinking");
		pthread_mutex_lock(((t_ph *)arg)->st->lock);
	}
	pthread_mutex_unlock(((t_ph *)arg)->st->lock);
	return (NULL);
}

void	watch(t_ph *philosophers, t_st *st, int id)
{
	t_tv	temp;

	while (1)
	{
		id = (id + 1) * (id < st->nop - 1);
		pthread_mutex_lock(philosophers[id].lock);
		gettimeofday(&temp, NULL);
		if (tv2ul(temp) - st->start_time > philosophers[id].lasteaten
			&& (tv2ul(temp) - st->start_time - philosophers[id].lasteaten)
			> st->die_lap)
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
	while (--id >= 0)
		pthread_join(st->philosophers[id], NULL);
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
	watch(philosophers, settings, -1);
	free_data(philosophers, settings);
	return (0);
}
