/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:41:25 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/04 19:22:28 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function checks if the string parsed contains wildcard symbol '*'.
 * 
 * @param str The string parsed for checking.
 * @return Returns TRUE upon found; otherwise returns FALSE.
*/
t_bool	found_wildcard(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '*')
			return (TRUE);
	}
	return (FALSE);
}

/**
 * Wildcard handling function, where function will join the double char arrays
 * containing the commands and options/arguments into a single string with
 * spaces as its delimination. Should there be a wildcard (*) symbol found,
 * the dereferenced string of the double char array will be expanded to string
 * with matching text given the wildcard pattern, before joining them back to
 * said single string.
 * 
 * @param arg The double char array containing the initial commands and options/
 * arguments.
 * @return Function will return a expanded string.
*/
char	*handle_wildcard(char **arg)
{
	int		i;
	char	*expand;
	char	*bigstr;

	bigstr = ft_strdup(arg[0]);
	i = 0;
	while (arg[++i] != NULL)
	{
		if (found_wildcard(arg[i]) == TRUE)
		{
			expand = expand_wildcard(arg[i]);
			if (expand != NULL)
			{
				bigstr = join_str(bigstr, ft_strdup(" "), expand);
				continue ;
			}
		}
		bigstr = join_str(bigstr, ft_strdup(" "), ft_strdup(arg[i]));
	}
	free_doublearray(arg);
	return (bigstr);
}
