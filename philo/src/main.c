/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 10:37:26 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/06/06 09:55:51 by lbiasuz          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	if (!allowed_input(argc, argv))
		return (1);
}