/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 22:40:45 by zwong             #+#    #+#             */
/*   Updated: 2022/07/12 22:40:46 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*newstr;
	size_t	total_len;

	if (!s1 || !s2)
		return (0);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	newstr = (char *)ft_calloc(total_len, sizeof(char));
	if (!newstr)
		return (0);
	ft_strlcat(newstr, s1, total_len);
	ft_strlcat(newstr, s2, total_len);
	return (newstr);
}
