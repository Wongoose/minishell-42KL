/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:30:56 by zwong             #+#    #+#             */
/*   Updated: 2023/05/08 18:30:56 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	replace_pwd(t_vars *vars, char *oldstr)
{
	char	**newpwd;
	char	**oldpwd;

	oldpwd = ft_calloc(3, sizeof(char *));
	oldpwd[0] = ft_strdup("");
	oldpwd[1] = join_str(ft_strdup("OLDPWD="), NULL, oldstr);
	add_or_replace(vars, oldpwd);
	free_doublearray(oldpwd);
	newpwd = ft_calloc(3, sizeof(char *));
	newpwd[0] = ft_strdup("");
	newpwd[1] = join_str(ft_strdup("PWD="), NULL, getcwd(NULL, 0));
	add_or_replace(vars, newpwd);
	free_doublearray(newpwd);
}

int	func_cd(t_vars *vars, char **args)
{
	char	*path;
	char	*oldstr;

	oldstr = getcwd(NULL, 0);
	if (args[1] == NULL || args[1][0] == '~')
	{
		path = get_envp_value(vars->envp, ft_strdup("HOME"));
		if (path == NULL)
			ft_putstr_fd("HOME not set\n", STDERR_FILENO);
		else
		{
			path = ft_strdup(path);
			if (args[1] != NULL)
				path = join_str(path,
						NULL, ft_substr(args[1], 1, ft_strlen(args[1]) - 1));
			if (chdir(path) < 0)
				perror(path);
			free(path);
		}
	}
	else if (chdir(args[1]) < 0)
		perror(args[1]);
	replace_pwd(vars, oldstr);
	return (0);
}
