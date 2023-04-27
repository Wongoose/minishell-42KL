/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:00:08 by chenlee           #+#    #+#             */
/*   Updated: 2023/04/27 18:01:04 by chenlee          ###   ########.fr       */
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

	i = -1;
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
