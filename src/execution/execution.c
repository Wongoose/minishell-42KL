/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:00:08 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/25 18:01:35 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int	call_execve(t_vars *vars, t_pipe cmdlst)
{
	int		i;
	int		ret;
	char	*pathname;
	char	*temp;
	
	i = -1;
	while (vars->path[++i] != NULL)
	{
		temp = ft_strjoin(vars->path[i], "/");
		pathname = ft_strjoin(temp, cmdlst.cmd);
		ret = execve(pathname, cmdlst.arg, NULL);
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
	int		i;

	i = -1;
	while (vars->functions[++i] != NULL)
	{
		if (ft_strcmp(cmdlst.cmd, vars->functions[i]) == 0)
		{
			vars->func[i](vars, cmdlst.arg);
			return (0);
		}
	}
	return (call_execve(vars, cmdlst));
}
