/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:58:43 by zwong             #+#    #+#             */
/*   Updated: 2022/07/12 16:58:44 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dupstr;
	int		i;

	dupstr = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!dupstr)
		return (0);
	i = 0;
	while (s1[i])
	{
		dupstr[i] = s1[i];
		i++;
	}
	dupstr[i] = 0;
	return (dupstr);
}
