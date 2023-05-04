/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:41:25 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/04 19:04:54 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_dp(t_bool **dp, int p_len)
{
	int	i;

	i = -1;
	while (++i <= p_len)
		free(dp[i]);
	free(dp);
}

/**
 * When populating cells within the dp table, two while loops are used that
 * iterate through the characters in the pattern and text strings respectively.
 * 
 * In cases where a '*' wildcard appears within the pattern string, fill current
 * cell, taking into account either:
 *   i. The value of the previous row (dp[i 1][j]) or
 *   ii. The value of the previous column (dp[i][j 1]).
 * This function checks if zero or more characters can exist between matched
 * sub patterns.
 * 
 * In cases where no wildcard appears, cells are further populated with diagonal
 * cells to the top left.
 * 
 * Example: text = "abcde", pattern = "ab*"
 *      a  b  c  d  e
 *    -----------------
 *  a | T  F  F  F  F
 *  b | F  T  F  F  F
 *  * | F  T  T  T  T
 * 
 * @param dp The table that stores the boolean comparison of the pattern and
 * text strings
 * @param pattern The pattern string
 * @param text The text string
 * @return Function does not return
*/
void	fill_dp_table(t_bool **dp, char *pattern, char *text)
{
	int	i;
	int	j;
	int	p_len;
	int	t_len;

	p_len = ft_strlen(pattern);
	t_len = ft_strlen(text);
	dp[0][0] = TRUE;
	i = 0;
	while (++i <= p_len)
	{
		j = 0;
		if (pattern[i - 1] == '*')
		{
			dp[i][0] = dp[i - 1][0];
			while (++j <= t_len)
				dp[i][j] = (dp[i - 1][j] || dp[i][j - 1]);
		}
		else
			while (++j <= t_len)
				if (pattern[i - 1] == text[j - 1])
					dp[i][j] = dp[i - 1][j - 1];
	}
}

// void	print_dp(t_bool **dp, int p, int t, char *pat, char *txt)
// {
// 	int	i;
// 	int	j;

// 	(void)txt;
// 	dprintf(2, "pat=%d && txt=%d\n", p, t);
// 	i = -1;
// 	dprintf(2, "  ");
// 	while (++i < p)
// 		dprintf(2, "%c ", pat[i]);
// 	i = -1;
// 	while (++i < p)
// 	{
// 		j = -1;
// 		while (++j < t)
// 			dprintf(2, "%d ", dp[i][j]);
// 		dprintf(2, "\n");
// 	}
// 	dprintf(2, "\n\n");
// }

/**
 * Main wilcard matching algorithm, initialize a 2D boolean table of size
 * pattern_len and text_len, and set all index to FALSE. This table will
 * be used to compare both strings.
 * 
 * @param pattern The pattern string containing the wildcard
 * @param text The text string to compare
 * @param pattern_len The length of pattern string
 * @param text_len The length of text string
*/
int	is_in_wildcard(char *pattern, char *text, int pattern_len, int text_len)
{
	int		i;
	int		result;
	t_bool	**dp;

	dp = malloc(sizeof(t_bool *) * (pattern_len + 1));
	i = -1;
	while (++i <= pattern_len)
	{
		dp[i] = malloc(sizeof(t_bool) * (text_len + 1));
		ft_memset(dp[i], FALSE, sizeof(t_bool) * (text_len + 1));
	}
	fill_dp_table(dp, pattern, text);
	// print_dp(dp, pattern_len, text_len, pattern, text);
	result = dp[pattern_len][text_len];
	ft_free_dp(dp, pattern_len);
	return (result);
}

char	*readdir_loop(DIR *dir, char *wc_str)
{
	struct dirent	*entry;
	char			*expanded_str;

	expanded_str = ft_strdup("");
	while (1)
	{
		entry = readdir(dir);
		if (entry != NULL)
		{
			if (entry->d_name[0] == '.')
				continue ;
			if (is_in_wildcard(wc_str, entry->d_name, ft_strlen(wc_str),
					ft_strlen(entry->d_name)))
				expanded_str = join_str(expanded_str, ft_strdup(" "),
						ft_strdup(entry->d_name));
		}
		else
			break ;
	}
	return (expanded_str);
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
	char			*expanded_str;

	printf("str=%s\n", wc_str);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		exit(error("getcwd()", "Failed"));
	dir = opendir(cwd);
	if (dir == NULL)
		exit(error("opendir()", "Failed"));
	expanded_str = readdir_loop(dir, wc_str);
	closedir(dir);
	if (expanded_str[0] == '\0')
		return (free(expanded_str), ft_strdup(wc_str));
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
