/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 18:16:31 by zwong             #+#    #+#             */
/*   Updated: 2022/07/07 18:16:33 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	find;
	unsigned char	*str;

	find = (unsigned char)c;
	str = (unsigned char *)s;
	while (n--)
	{
		if (*str == find)
			return ((void *)str);
		str++;
	}
	return (0);
}
