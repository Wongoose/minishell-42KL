/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_export_unset_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:19:27 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/12 17:36:10 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function prints the whole environment variable.
 * 
 * @param vars The struct containing the environment variable
 * @return Function doesn't return
*/
void	print_envp(t_vars *vars)
{
	int	i;
	int	j;
	int	count;
	
	i = -1;
	while (vars->envp[++i] != NULL)
	{
		j = -1;
		count = 0;
		while (vars->envp[i][++j] != 0)
		{
			write(1, &vars->envp[i][j], 1);
			if (vars->envp[i][j] == '=' && count == 0)
			{
				write(1, "\"", 1);
				count++;
			}
		}
		if (count != 0)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
}

/**
 * A modified version of ft_split, where it splits the string into 2,
 * deliminated by the first occurance of the equal character in the string.
 * 
 * @param str The string parsed for splitting
 * @return Function returns the new string array.
*/
char	**equal_split(char *str)
{
	char	**ret;
	char	*position;

	position = ft_strchr(str, '=');
	ret = malloc(sizeof(char *) * 3);
	ret[0] = ft_substr(str, 0, (position - str));
	if (position == 0)
		ret[1] = NULL;
	else
		ret[1] = ft_strdup(position + 1);
	ret[2] = NULL;
	return (ret);
}

/**
 * Error handling when invalid input is detected
 * 
 * @param condition The condition of the error
 * @param var The input string
 * @param name The type of shell command
 * @return Function returns 1
*/
int	export_unset_error(int condition, char *var, char *name)
{
	if (condition == 1)
		ft_printf("minishell: %s: '%s': not a valid identifier\n", name, var);
	return (1);
}

/**
 * Function verifies if the key parsed is valid, which the key is made of
 * alphanumericals and underscore (except for the first character which should
 * include alphabets and underscore)
 * 
 * @param variable The key parsed for addition or replacement
 * @return Function returns true if verification succeed; otherwise returns
 * false
*/
t_bool	verify_variable(char *variable)
{
	int	i;

	i = -1;
	while (variable[++i] != 0)
	{
		if (i == 0 && !(variable[i] == '_' || ft_isalpha(variable[i])))
			return (FALSE);
		else if (variable[i] != '_' || !ft_isalnum(variable[i]))
			return (FALSE);
	}
	return (TRUE);
}

t_bool	validate_unset(char *variable)
{
	int	i;

	i = -1;
	if (ft_isalpha(variable[++i]) == 0)
		return (FALSE);
	while (variable[++i] != '\0')
	{
		if (ft_isalnum(variable[i]) == 0)
			return (FALSE);
	}
	return (TRUE);
}
