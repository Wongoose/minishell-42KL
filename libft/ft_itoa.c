/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:56:58 by zwong             #+#    #+#             */
/*   Updated: 2022/07/13 14:56:59 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_size(long n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*strnum;
	size_t		size;
	long		nbr;

	size = 0;
	nbr = (long)n;
	if (nbr < 0)
	{
		nbr *= -1;
		size++;
	}
	size += get_size(nbr);
	strnum = (char *)malloc(sizeof(char) * (size + 1));
	if (!strnum)
		return (0);
	strnum[size] = 0;
	while (size--)
	{
		strnum[size] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (n < 0)
		strnum[0] = '-';
	return (strnum);
}
