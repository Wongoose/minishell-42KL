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

int	func_cd(t_vars *vars, char **args)
{
	char	*path;
	char	**temp;

	if (args[1] == NULL || args[1][0] == '~')
	{
		path = args[1];
		path = get_envp_value(vars->envp, ft_strdup("HOME"));
		if (path == NULL)
			ft_putstr_fd("HOME not set\n", STDERR_FILENO);
		else if (args[1] != NULL)
			path = join_str(ft_strdup(path),
					NULL, ft_substr(args[1], 1, ft_strlen(args[1]) - 1));
		if (chdir(path) < 0)
			perror(path);
	}
	else if (chdir(args[1]) < 0)
		perror(args[1]);
	temp = ft_calloc(3, sizeof(char *));
	temp[1] = join_str(ft_strdup("PWD="), NULL, ft_strdup(getcwd(NULL, 0)));
	add_or_replace(vars, temp);
	free(temp);
	return (0);
}
