/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz@student.42sp.org.br <lbiasuz>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:22:14 by lbiasuz@stu       #+#    #+#             */
/*   Updated: 2023/09/20 22:54:51 by lbiasuz@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	yeah_its_over(t_st *st, t_tv time, int id)
{
	pthread_mutex_lock(st->lock);
	st->its_over = 1;
	pthread_mutex_unlock(st->lock);
	printf("%ld %d %s\n",
		(tv2ul(time) - st->start_time), id, "died");
}

int	is_it_over(t_ph *ph, t_st *st, t_tv time, int id)
{
	if (ph[id].lasteaten == 0)
		return (tv2ul(time) - st->start_time > st->die_lap);
	return ((tv2ul(time) - ph[id].lasteaten) > st->die_lap);
}

void	its_clearly_over(t_st *st)
{
	int	id;

	id = st->nop;
	while (--id >= 0)
		pthread_join(st->philosophers[id], NULL);
}

void	watch(t_ph *philosophers, t_st *st, int id)
{
	while (1)
	{
		id = (id + 1) * (id < st->nop - 1);
		pthread_mutex_lock(philosophers[id].lock);
		if (is_it_over(philosophers, st, get_temp(), id))
		{
			yeah_its_over(st, get_temp(), id);
			pthread_mutex_unlock(philosophers[id].lock);
			break ;
		}
		pthread_mutex_lock(st->lock);
		if (st->satisfied >= st->nop)
		{
			pthread_mutex_unlock(st->lock);
			pthread_mutex_unlock(philosophers[id].lock);
			break ;
		}
		pthread_mutex_unlock(st->lock);
		pthread_mutex_unlock(philosophers[id].lock);
		usleep(1000);
	}
	its_clearly_over(st);
}
