/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz <lbiasuz@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:15:38 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/06/13 22:00:08 by lbiasuz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	ft_isspace(char c)
{
	if (c == '\f' || c == '\n'
		|| c == '\r' || c == '\t'
		|| c == '\v' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	n;

	i = 0;
	n = 1;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
		n = -1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (ft_isdigit(*nptr))
	{
		i = (i * 10) + (*nptr - 48);
		nptr++;
	}
	return (i * n);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char			*dest;
	int				check;
	unsigned int	i;

	i = 0;
	check = nmemb > size;
	if ((nmemb * size) < ((nmemb * check) + (size * !check)))
		return (NULL);
	dest = malloc(nmemb * size);
	if (!dest)
		return (NULL);
	while (i < (nmemb * size))
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
