/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:29:10 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/12 17:09:36 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function replaces the current environment variable array with new array
 * containing the new variable key/value
 * 
 * @param vars The main struct containing the environment variables
 * @param new_var The new key/value to add
 * @return Function returns 1 after successful replacement of env array
*/
int	add_env(t_vars *vars, char *new_var)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (vars->envp[i] != NULL)
		i++;
	new_envp = (char **)ft_calloc(i + 2, sizeof(char *));
	i = -1;
	while (vars->envp[++i] != NULL)
		new_envp[i] = ft_strdup(vars->envp[i]);
	free_doublearray(vars->envp);
	new_envp[i] = ft_strdup(new_var);
	vars->envp = new_envp;
	return (1);
}

/**
 * Function replaces the value of the key in the environment variable
 * 
 * @param vars The main struct containing the environment variables
 * @param new_var The new key's value to replace
 * @param location The index of the environment variable array which points to
 * the key for value-replacement
 * @return Function returns 1 after successful replacement of the value
*/
int	replace_env(t_vars *vars, char **new_var, int location)
{
	char	*temp;
	char	*str;

	temp = ft_strjoin(new_var[0], "=");
	str = ft_strjoin(temp, new_var[1]);
	free(temp);
	free(vars->envp[location]);
	vars->envp[location] = str;
	return (1);
}

/**
 * Function checks if the key parsed exists in the environment variable
 * 
 * @param env The current environment variables
 * @param our The new key parsed for new addition or replacement
 * @return If the key exists in the environment variable, returns the index of
 * the variable among the env; If the key does not exist, returns -1
*/
int	check_occurance(char **env, char **our)
{
	int		i;
	int		ret;
	size_t	len;
	char	**ori;

	i = -1;
	ret = -1;
	while (env[++i] != NULL && env[i][0] != 0)
	{
		ori = ft_split(env[i], '=');
		len = ((ft_strlen(ori[0]) >= ft_strlen(our[0])) * ft_strlen(ori[0]))
			+ ((ft_strlen(ori[0]) < ft_strlen(our[0])) * ft_strlen(our[0]));
		if (ft_strncmp(ori[0], our[0], len) == 0)
			ret = i;
		free_doublearray(ori);
	}
	return (ret);
}

/**
 * Function determines whether to add a new key with its value into the
 * environment variable, or to replace the value if the key already exists.
 * 
 * @param vars The struct containing the environment variable
 * @param args The arguments containing the new key and value
 * @return Function returns 0 on success execution; returns 1 when failed.
*/
int	add_or_replace(t_vars *vars, char **args)
{
	int		ret;
	int		add_ret;
	int		i;
	char	**key_val;

	i = 0;
	while (args[++i] != NULL)
	{
		key_val = equal_split(args[i]);
		if (verify_variable(key_val[0]) != TRUE)
			return (export_unset_error(1, key_val[0], "export"));
		ret = check_occurance(vars->envp, key_val);
		if (ret != -1 && key_val[1] != NULL)
			add_ret = replace_env(vars, key_val, ret);
		else if (ret == -1)
			add_ret = add_env(vars, args[i]);
		free_doublearray(key_val);
		if (add_ret == 1)
			break ;
	}
	return (0);
}

/**
 * Recreation of the export command in shell, where if no argument is parsed,
 * displays the whole environment variable; otherwise, either add the new
 * variable, or replace its value
 * 
 * @param vars The struct containing the environment variable
 * @param args The arguments containing the key and possibly its value
 * @return Function returns 0 on success execution; returns 1 when failed.
*/
int	func_export(t_vars *vars, char **args)
{
	int	ret;

	ret = 0;
	if (args[1] == NULL || args[1][0] == '#')
		print_envp(vars);
	else
		vars->last_errno = add_or_replace(vars, args);
	return (ret);
}
