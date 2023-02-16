/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 21:32:31 by zwong             #+#    #+#             */
/*   Updated: 2022/07/04 21:32:32 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// The bzero function is used to erase the given memory area with zero bytes

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *) s;
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
}
