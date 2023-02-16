/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:46:45 by zwong             #+#    #+#             */
/*   Updated: 2022/07/04 21:46:46 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Create new ptrs to type cast dst and src
// 29: dst_str = (char *) dst;
// 30: src_str = (char *) src;

// Return pointer which is at the beginning
// 38: return (dst);

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_str;
	char	*src_str;

	if (!dst && !src)
		return (0);
	i = 0;
	dst_str = (char *) dst;
	src_str = (char *) src;
	while (i < n)
	{
		*dst_str = *src_str;
		dst_str++;
		src_str++;
		i++;
	}
	return (dst);
}
