/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:52:05 by zwong             #+#    #+#             */
/*   Updated: 2022/07/07 20:52:06 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*search_ptr;
	size_t	i;

	search_ptr = (char *)haystack;
	i = 0;
	if (!*needle)
		return ((char *)haystack);
	while (i < len && *search_ptr)
	{
		if (ft_strncmp(search_ptr, needle, ft_strlen(needle)) == 0)
		{
			if (i + ft_strlen(needle) <= len)
				return (search_ptr);
		}
		search_ptr++;
		i++;
	}
	return (0);
}
