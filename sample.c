/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sample.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zharzi <zharzi@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 00:22:28 by zharzi            #+#    #+#             */
/*   Updated: 2023/02/06 12:29:05 by zharzi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cutter.h"

int	ft_abs(int x)
{
	if (x < 0)
		return (-x);
	return (x);
}

#include "cutter.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || *nptr == ' ')
		nptr++;
	if (*nptr == '-')
		k = -1;
	else if (*nptr == '+' || (*nptr >= '0' && *nptr <= '9'))
		k = 1;
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		if (i != 0)
			i *= 10;
		i += *nptr - '0';
		nptr++;
	}
	return (i * k);
}

#include "cutter.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*ptr;

	if ((nmemb == SIZE_MAX || size == SIZE_MAX) && (nmemb > 1 || size > 1))
		return (NULL);
	ptr = (char *)malloc(size * nmemb);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
