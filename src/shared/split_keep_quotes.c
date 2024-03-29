/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_keep_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:10:52 by zwong             #+#    #+#             */
/*   Updated: 2023/05/08 19:23:37 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(char const *s)
{
	int		words;
	int		i;
	char	quote_t;

	quote_t = 0;
	words = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		if (!quote_t && ft_isquote(s[i]))
			quote_t = s[i++];
		else if (quote_t && s[i] == quote_t)
			quote_t = 0;
		if (s[i])
			words++;
		while (quote_t && (s[i] != quote_t && s[i]))
			i++;
		if (quote_t && s[i] == quote_t)
			quote_t = 0;
		while (s[i] != ' ' && s[i])
			i++;
	}
	return (words);
}

char	*exclude_quotes(char *str)
{
	char	*new;
	char	quote_t;
	int		i;
	int		j;

	if (!(ft_strchr(str, '"') || ft_strchr(str, '\'')))
		return (str);
	new = (char *)ft_calloc(ft_strlen(str), 1);
	i = -1;
	j = 0;
	quote_t = 0;
	while (str[++i])
	{
		if (!quote_t && ft_isquote(str[i]))
			quote_t = str[i];
		else if (quote_t && str[i] == quote_t)
			quote_t = 0;
		else if (str[i] != quote_t)
			new[j++] = str[i];
	}
	new[j] = 0;
	free(str);
	return (new);
}

static int	find_end(char *s, int start, char *quote_t)
{
	int	end;

	end = start + 1;
	while (*quote_t && (s[end] != *quote_t && s[end]))
		end++;
	if (*quote_t && s[end] == *quote_t)
		*quote_t = 0;
	while (s[end] != ' ' && s[end])
	{
		end++;
		if (ft_isquote(s[end]))
			break ;
	}
	return (end);
}

char	**split_keep_quotes(char *s)
{
	char	**splitstr;
	char	quote_t;
	int		start;
	int		end;
	int		i;

	splitstr = (char **)ft_calloc(count_words(s) + 1, sizeof(char *));
	quote_t = 0;
	start = 0;
	end = 0;
	i = -1;
	while (++i < count_words(s))
	{
		while (s[start] == ' ')
			start++;
		quote_t = update_quote_t(quote_t, s[start]);
		end = find_end(s, start, &quote_t);
		splitstr[i]
			= join_str(splitstr[i], NULL, ft_substr(s, start, end - start));
		if (!quote_t && ft_isquote(s[end]))
			i--;
		start = end;
	}
	return (free(s), splitstr);
}
