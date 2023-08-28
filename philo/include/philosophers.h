/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 09:49:36 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/06/27 21:41:03 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <string.h> // memset
# include <stdio.h> // printf
# include <stdlib.h> // malloc, free
# include <unistd.h> // write
# include <sys/wait.h> // usleep
# include <sys/time.h> // gettimeofday
# include <pthread.h> // pthread_create, pthread_detach, pthread_join,
 					  // pthread_mutex_init, pthread_mutex_destroy,
					  // pthread_mutex_lock, pthread_mutex_unlock

void	watch(t_tb);

int		ft_atol(const char *nptr);
void	*ft_calloc(size_t nmemb, size_t size);

# define USAGE "number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat] \n\
Times must be in miliseconds and should not be less than 60\n"

typedef struct timeval t_tv;

typedef struct	s_ph {
	int				id;
	int				is_dead;
	int				is_eating;
	int				is_sleeping;
	unsigned long	lasteaten;
	pthread_mutex_t *fork[2];
} t_ph; //type_philosopher

typedef struct s_st {
	long				nop;
	unsigned long		start_time;
	unsigned long		eat_lap;
	unsigned long		sleep_lap;
	unsigned long		die_lap;
	long				servings;
	int					its_over;
	pthread_mutex_t		*forks;
	pthread_t			*philosophers;
} t_st; //type_settings

#endif