/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:41:25 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/17 01:37:42 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function checks if the first i characters of the pattern match the first j
 * characters of the text. The algorithm handles wildcard
 * characters in the pattern by considering two cases: either the wildcard
 * character matches zero characters in the text, or the wildcard character
 * matches one or more characters in the text.
*/
int	is_in_wildcard(char *pattern, char *text, int pattern_len, int text_len)
{
	int	i;
	int	j;
	int	dp[pattern_len + 1][text_len + 1];

	ft_memset(dp, 0, sizeof(dp));
	dp[0][0] = 1;
	i = 0;
	while (++i <= pattern_len && pattern[i - 1] == '*')
		dp[i][0] = 1;
	i = 0;
	while (++i <= pattern_len)
	{
		j = 0;
		while (++j <= text_len)
		{
			if (pattern[i - 1] == '*')
				dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
			else if (pattern[i - 1] == text[j - 1])
				dp[i][j] = dp[i - 1][j - 1];
			else
				dp[i][j] = 0;
		}
	}
	return (dp[pattern_len][text_len]);
}

/**
 * Function calls readdir() which gets a pointer to a dirent structure
 * describing a directory entry in the directory stream, in which contains
 * character pointer "d_name", which points to a string that gives the name of
 * a file in the directory. This string will then be compared if it matches the
 * wildcard pattern.
 * Every call to readdir() overwrites data produced by its previous call.
 * 
 * @param wc_str The wildcard pattern string parsed for comparison.
 * @return Function returns all matches in the directory, concatenated into a
 * single string with spaces as delimitation.
*/
char	*expand_wildcard(char *wc_str)
{
	DIR				*dir;
	char			cwd[256];
	struct dirent	*entry;
	char			*expanded_str;

	expanded_str = NULL;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		exit(error("getcwd()", "Failed"));
	if ((dir = opendir(cwd)) == NULL)
		exit(error("opendir()", "Failed"));
	while ((entry = readdir(dir)) != NULL)
	{
		if (is_in_wildcard(wc_str, entry->d_name, ft_strlen(wc_str),
				ft_strlen(entry->d_name)))
		{
			if (expanded_str == NULL)
				expanded_str = ft_strjoin(entry->d_name, " ");
			else
				expanded_str = join_str(expanded_str, ft_strdup(" "),
					ft_strdup(entry->d_name));
		}
	}
	closedir(dir);
	return (expanded_str);
}

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
 * @return Function will replace the initial double char array with the single
 * string splitted into double char array, with spaces as its deliminator.
*/
char	**handle_wildcard(char **arg)
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
	arg = ft_split(bigstr, ' ');
	return (free(bigstr), arg);
}
