/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz@student.42sp.org.br <lbiasuz>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 22:06:45 by lbiasuz@stu       #+#    #+#             */
/*   Updated: 2023/09/05 22:35:44 by lbiasuz@stu      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	allowed_input(int argc, char **argv)
{
	(void)argv;
	if (argc > 6 || argc < 5)
	{
		write(2, USAGE, sizeof(USAGE) - 1);
		return (0);
	}
	return (1);
}
