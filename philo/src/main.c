/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:37:26 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/07/02 16:46:56 by lbiasuz          ###   ########.fr       */
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

int		philosopher_lifecycle(t_st	*settings, t_ph *philosopher);

void	init_sim(t_st *settings)
{
	int		i;
	t_ph	*philosopher;
	
	i = 0;
	settings->philosophers = (t_ph **) ft_calloc(settings->nop, sizeof(t_ph*));
	while (i < settings->nop)
	{
		philosopher = (t_ph **) ft_calloc(1, sizeof(t_ph *));
		philosopher 
		pthread_create(settings->philosophers[i], NULL, philosopher_lifecycle, (void *) philosopher);
		i++;
	}
}

t_st	*init_settings(char **args, int argc)
{
	t_st	*settings;

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
	gettimeofday(&settings->start_time, NULL);
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
		single_philo_exec();
	else
		multiple_philo_exec();

}
// (pthread_mutex_t **) ft_calloc(settings->nop, sizeof(pthread_mutex_t));