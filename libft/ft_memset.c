/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:24:07 by zwong             #+#    #+#             */
/*   Updated: 2022/07/04 21:24:08 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The memset function is used to fill a block of memory with a particular value

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*write_ptr;

	i = 0;
	write_ptr = (unsigned char *) b;
	while (i < len)
	{
		write_ptr[i] = (unsigned char) c;
		i++;
	}
	return (b);
}
