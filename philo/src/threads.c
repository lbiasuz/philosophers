/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz@student.42sp.org.br <lbiasuz>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:25:23 by lbiasuz@stu       #+#    #+#             */
/*   Updated: 2023/09/16 18:38:32 by lbiasuz@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	log_action(t_ph *ph, char *action)
{
	t_tv	temp;

	gettimeofday(&temp, NULL);
	pthread_mutex_lock(ph->st->lock);
	if (ph->st->its_over)
	{
		pthread_mutex_unlock(ph->st->lock);
		return ;
	}
	printf("%ld %d %s\n",
		(tv2ul(temp) - ph->st->start_time), ph->id, action);
	pthread_mutex_unlock(ph->st->lock);
}

void	lock_forks(t_ph *ph)
{
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
}

void	eat_spaghetti(t_ph *ph)
{
	pthread_mutex_lock(ph->lock);
	ph->lasteaten = tv2ul(get_temp());
	ph->times_eaten++;
	pthread_mutex_unlock(ph->lock);
	log_action(ph, "is eating");
	usleep(ph->st->eat_lap * 1000);
}

void	*philosopher_lifecycle(void *arg)
{
	pthread_mutex_lock(((t_ph *)arg)->st->lock);
	while (!((t_ph *)arg)->st->its_over && (((t_ph *)arg)->st->servings == -1
			|| ((t_ph *)arg)->times_eaten < ((t_ph *)arg)->st->servings))
	{
		pthread_mutex_unlock(((t_ph *)arg)->st->lock);
		if (((t_ph *)arg)->st->nop == 1)
		{
			pthread_mutex_lock(((t_ph *)arg)->st->lock);
			continue ;
		}
		lock_forks(((t_ph *)arg));
		eat_spaghetti(((t_ph *)arg));
		pthread_mutex_unlock(((t_ph *)arg)->fork[0]);
		pthread_mutex_unlock(((t_ph *)arg)->fork[1]);
		log_action(((t_ph *)arg), "is sleeping");
		usleep(((t_ph *)arg)->st->sleep_lap * 1000);
		log_action(((t_ph *)arg), "is thinking");
		pthread_mutex_lock(((t_ph *)arg)->st->lock);
	}
	((t_ph *)arg)->st->satisfied += (
			((t_ph *)arg)->times_eaten >= ((t_ph *)arg)->st->servings);
	pthread_mutex_unlock(((t_ph *)arg)->st->lock);
	return (NULL);
}
