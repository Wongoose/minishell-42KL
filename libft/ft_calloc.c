/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:35:49 by zwong             #+#    #+#             */
/*   Updated: 2022/07/12 16:35:50 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*range;
	size_t	total;

	if (count >= SIZE_MAX || size >= SIZE_MAX)
		return (0);
	total = size * count;
	range = malloc(total);
	if (!range)
		return (0);
	ft_bzero(range, total);
	return (range);
}
