/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbiasuz@student.42sp.org.br <lbiasuz>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 22:15:38 by lbiasuz           #+#    #+#             */
/*   Updated: 2023/09/12 22:44:17 by lbiasuz@stu      ###   ########.fr       */
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

int	ft_atol(const char *nptr)
{
	long	i;

	i = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		i = (i * 10) + (*nptr - 48);
		nptr++;
	}
	return (i);
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

unsigned long	tv2ul(t_tv time)
{
	return ((unsigned long)((time.tv_sec * 1000) + (time.tv_usec / 1000)));
}

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
	printf("%ld philosopher %d %s\n",
		(tv2ul(temp) - ph->st->start_time), ph->id, action);
	pthread_mutex_unlock(ph->st->lock);
}
