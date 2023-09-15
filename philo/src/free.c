/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz@student.42sp.org.br <lbiasuz>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 10:56:57 by lbiasuz@stu       #+#    #+#             */
/*   Updated: 2023/09/14 22:33:54 by lbiasuz@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	free_data(t_ph *philosophers, t_st *settings)
{
	int	i;

	i = 0;
	while (i < settings->nop)
	{
		pthread_mutex_destroy(philosophers[i].lock);
		free(philosophers[i].lock);
		i++;
	}
	free(settings->philosophers);
	pthread_mutex_destroy(settings->forks);
	pthread_mutex_destroy(settings->lock);
	free(settings->forks);
	free(settings->lock);
	free(settings);
	free(philosophers);
}
