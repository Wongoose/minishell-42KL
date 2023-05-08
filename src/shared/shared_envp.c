/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shared_envp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 18:14:25 by zwong             #+#    #+#             */
/*   Updated: 2023/05/08 18:44:04 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Function gets the value of the environment variable.
 * 
 * @param envp The environment variable array
 * @param key The key with value of interest
 * @return The value of the key
*/
char	*get_envp_value(char **envp, char *key)
{
	int		i;
	char	*value;

	i = 0;
	while (envp[i])
	{
		value = ft_strnstr(envp[i], key, ft_strlen(key));
		if (value)
		{
			value += ft_strlen(key) + 1;
			break ;
		}
		i++;
	}
	free(key);
	return (value);
}

/**
 * Function creates a duplicate from the environment variable parsed from main,
 * to prevent directly modifying the keys and values of the parent shell.
 * 
 * @param envp the environment variable of the parent shell
 * @return Returns a copy of environment variable
*/
char	**dup_envp(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i] != NULL)
		i++;
	new_envp = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	new_envp[i] = 0;
	return (new_envp);
}

char	*handle_env_dollar(t_vars *vars, char *str, char *new_str, int *i)
{
	int		j;
	char	*expanded;

	j = 0;
	if (str[++(*i)] == '?')
	{
		new_str = join_str(new_str, NULL, ft_itoa(vars->last_errno));
		j = ft_strlen(ft_itoa(vars->last_errno));
	}
	else
	{
		while (ft_isalnum(str[j + *i]))
			j++;
		expanded = get_envp_value(vars->envp, ft_substr(str, *i, j));
		if (expanded)
			new_str = join_str(new_str, NULL, ft_strdup(expanded));
		*i += j - 1;
	}
	return (new_str);
}

char	*handle_wildcard_expansion(char *str, int *i, char *new_str)
{
	char	*temp;
	int		j;

	j = *i;
	while (str[j] != ' ' && str[j])
		j++;
	temp = join_str(new_str, NULL, ft_substr(str, *i, j - *i));
	new_str = handle_wildcard(ft_split(temp, ' '));
	*i = j - 1;
	return (free(temp), new_str);
}

char	*expand_env_dollar(t_vars *vars, char *str)
{
	int		i;
	char	*new_str;
	char	quote_t;

	quote_t = 0;
	new_str = NULL;
	i = 0;
	while (str[i] != '\0')
	{
		quote_t = update_quote_t(quote_t, str[i]);
		if (str[i] == '$' && quote_t != '\'' && str[i + 1] != ' ')
			new_str = handle_env_dollar(vars, str, new_str, &i);
		else if (str[i] == '*' && !quote_t)
			new_str = handle_wildcard_expansion(str, &i, new_str);
		else
			new_str = join_str(new_str, NULL, ft_substr(str, i, 1));
		i++;
	}
	return (free(str), new_str);
}

// char	*expand_env_dollar(t_vars *vars, char *str)
// {
// 	int		i;
// 	int		j;
// 	char	*new_str;
// 	char	*expanded;
// 	char	quote_t;

// 	quote_t = 0;
// 	new_str = NULL;
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		j = 0;
// 		quote_t = update_quote_t(quote_t, str[i]);
// 		if (str[i] == '$' && quote_t != '\'' && str[i + 1] != ' ')
// 		{
// 			if (str[++i] == '?')
// 			{
// 				new_str = join_str(new_str, NULL, ft_itoa(vars->last_errno));
// 				j = ft_strlen(ft_itoa(vars->last_errno));
// 			}
// 			else
// 			{
// 				while (ft_isalnum(str[j + i]))
// 					j++;
// 				expanded = get_envp_value(vars->envp, ft_substr(str, i, j));
// 				if (expanded)
// 					new_str = join_str(new_str, NULL, ft_strdup(expanded));
// 				i += j - 1;
// 			}
// 		}
// 		else if (str[i] == '*' && !quote_t)
// 		{
// 			free(new_str);
// 			new_str = handle_wildcard(ft_split(str, ' '));
// 			break ;
// 		}
// 		if (!j)
// 			new_str = join_str(new_str, NULL, ft_substr(str, i, 1));
// 		i++;
// 	}
// 	free(str);
// 	return (new_str);
// }