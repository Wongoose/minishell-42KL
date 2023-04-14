/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:41:25 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/14 22:00:05 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_arg(char **arg)
{
	int	i;

	dprintf(2, "print_arg starts\n");
	i = -1;
	while (arg[++i] != NULL)
	{
		dprintf(2, "%d: %s\n", i, arg[i]);
	}
}

char	**to_split_or_not(char *bigstr, char **arg, t_bool found)
{
	char	**ret;
	
	if (found == TRUE)
	{
		free_doublearray(arg);
		ret = ft_split(bigstr, ' ');
	}
	else
		ret = arg;
	free(bigstr);
	// print_arg(ret);
	return (ret);
}

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
				expanded_str = ft_strdup(ft_strjoin(entry->d_name, " "));
			else
				expanded_str = join_str(expanded_str, ft_strdup(" "),
					ft_strdup(entry->d_name));
		}
	}
	closedir(dir);
	return (expanded_str);
}

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

char	**handle_wildcard(char **arg)
{
	int		i;
	t_bool	found;
	char	*expand;
	char	*bigstr;

	found = FALSE;
	bigstr = ft_strdup(arg[0]);
	i = 0;
	print_arg(arg);
	while (arg[++i] != NULL)
	{
		dprintf(2, "bigstr = [%s]\n", bigstr);
		if (found_wildcard(arg[i]) == TRUE)
		{
			found = TRUE;
			expand = expand_wildcard(arg[i]);
			bigstr = join_str(bigstr, " ", expand);
		}
		else
			bigstr = join_str(bigstr, " ", ft_strdup(arg[i]));
	}
	return (to_split_or_not(bigstr, arg, found));
}
