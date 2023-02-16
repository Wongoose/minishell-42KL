/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 06:37:43 by zwong             #+#    #+#             */
/*   Updated: 2022/07/13 06:37:45 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;

	words = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			words++;
		while (*s != c && *s)
			s++;
	}
	return (words);
}

char	**ft_split(char const *s, char c)
{
	char	**splitstr;
	size_t	start;
	size_t	end;
	size_t	i;

	splitstr = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!s || !splitstr)
		return (0);
	start = 0;
	end = 0;
	i = 0;
	while (i < count_words(s, c))
	{
		while (s[start] == c)
			start++;
		end = start;
		while (s[end] != c && s[end])
			end++;
		splitstr[i] = ft_substr(s, start, end - start);
		start = end;
		i++;
	}
	splitstr[i] = 0;
	return (splitstr);
}
