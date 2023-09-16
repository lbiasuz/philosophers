/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz@student.42sp.org.br <lbiasuz>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:37:26 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/09/16 18:28:34 by lbiasuz@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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
