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

	if (args[1] == 0)
	{
		path = get_envp_value(vars->envp, ft_strdup("HOME"));
		if (path == NULL)
			ft_putstr_fd("HOME not set\n", STDERR_FILENO);
		else if (chdir(path) < 0)
			perror(path);
	}
	else if (chdir(args[1]) < 0)
		perror(args[1]);
	return (0);
}
