/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:00:08 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/19 14:12:35 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	call_execve(t_vars *vars, t_pipe cmdlst)
{
	int		i;
	int		ret;
	char	*pathname;
	char	*temp;

	signal(SIGINT, SIG_DFL);
	i = -1;
	while (vars->path[++i] != NULL)
	{
		temp = ft_strjoin(vars->path[i], "/");
		pathname = ft_strjoin(temp, cmdlst.cmd);
		ret = execve(pathname, cmdlst.arg, vars->envp);
		free(temp);
		free(pathname);
		if (ret != -1)
			break ;
	}
	if (vars->path[i] == NULL)
		return (error(cmdlst.cmd, "command not found"));
	return (0);
}

int	execution(t_vars *vars, t_pipe cmdlst)
{
	int	i;
	// int	j;

	i = -1;
	// REMOVED by ZX, wildcards will be handled during tokenization
	
	// while (cmdlst.arg[++i] != NULL)
	// {
	// 	j = -1;
	// 	while (cmdlst.arg[i][++j] != '\0')
	// 		if (cmdlst.arg[i][j] == '*')
	// 			cmdlst.arg = handle_wildcard(cmdlst.arg);
	// }
	if (cmdlst.cmd == NULL)
		exit(0);
	i = -1;
	while (vars->functions[++i] != NULL)
	{
		if (ft_strcmp(cmdlst.cmd, vars->functions[i]) == 0)
			exit (vars->func[i](vars, cmdlst.arg));
	}
	return (call_execve(vars, cmdlst));
}
