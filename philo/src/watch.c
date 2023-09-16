/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz@student.42sp.org.br <lbiasuz>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 18:22:14 by lbiasuz@stu       #+#    #+#             */
/*   Updated: 2023/09/16 18:40:49 by lbiasuz@stu      ###   ########.fr       */
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
	return (tv2ul(time) - st->start_time > ph[id].lasteaten
		&& (tv2ul(time) - st->start_time - ph[id].lasteaten) > st->die_lap);
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
	t_tv	temp;

	while (1)
	{
		id = (id + 1) * (id < st->nop - 1);
		pthread_mutex_lock(philosophers[id].lock);
		gettimeofday(&temp, NULL);
		if (is_it_over(philosophers, st, temp, id))
		{
			yeah_its_over(st, temp, id);
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
	}
	its_clearly_over(st);
}
