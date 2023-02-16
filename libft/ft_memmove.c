/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 22:05:04 by zwong             #+#    #+#             */
/*   Updated: 2022/07/04 22:05:05 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Compare the memory position of dest and source
// if (d_ptr > s_ptr)

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*d_ptr;
	char	*s_ptr;

	if (!dst && !src)
		return (0);
	i = 0;
	d_ptr = (char *) dst;
	s_ptr = (char *) src;
	if (d_ptr > s_ptr)
	{
		while (len--)
		{
			d_ptr[len] = s_ptr[len];
		}
	}
	else
	{
		while (i < len)
		{
			d_ptr[i] = s_ptr[i];
			i++;
		}
	}
	return (dst);
}
