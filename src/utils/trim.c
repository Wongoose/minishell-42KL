/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 13:36:52 by zwong             #+#    #+#             */
/*   Updated: 2023/05/08 19:59:42 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_trim(char *str)
{
	int		i;
	int		j;
	char	*ret;

	if (!str)
		return (NULL);
	i = 0;
	j = ft_strlen(str) - 1;
	while (str[i] == ' ' && str[i])
		i++;
	while (j > 0 && str[j] == ' ')
		j--;
	if (j <= 0)
		ret = ft_strdup("");
	else
		ret = ft_substr(str, i, j - i + 1);
	free(str);
	return (ret);
}

int	update_paren_char(char c, int *paren)
{
	if (c == '(')
	{
		if (*paren == -1)
			*paren = 0;
		(*paren)++;
	}
	else if (c == ')')
		(*paren)--;
	return (*paren);
}

char	*ft_trim_paren(char *str)
{
	int		i;
	int		paren;
	char	*ret;
	char	*temp;

	if (!str || str[0] != '(')
		return (ft_trim(str));
	ret = ft_trim(str);
	i = -1;
	paren = -1;
	while (ret[++i])
	{
		if (update_paren_char(ret[i], &paren) == 0)
		{
			if (i == (int)(ft_strlen(ret) - 1))
			{
				temp = ft_substr(ret, 1, ft_strlen(ret) - 2);
				free(ret);
				ret = ft_trim_paren(temp);
			}
			break ;
		}
	}
	return (ft_trim(ret));
}
