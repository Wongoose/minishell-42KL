/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:00:08 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/05 14:57:45 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function will call execve to execute the commands. Function first loop
 * through the PATH and attempt to execute the command. On success, execve does
 * not return and exits; otherwise, returns -1.
 * 
 * @param vars The main struct of the program containing the main token trees
 * @param cmdlst The struct containing information of current command group,
 * including command and arguments, redirections, etc.
*/
void	call_execve(t_vars *vars, t_pipe cmdlst)
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
	{
		error(cmdlst.cmd, "command not found");
		exit(127);
	}
}

/**
 * Main execution function, where it will first check if the command if of
 * built-in functions, otherwise execute the command using execve.
 * 
 * @param vars The main struct of the program containing the main token trees
 * @param cmdlst The struct containing information of current command group,
 * including command and arguments, redirections, etc.
 * 
 * @return Function does not return
*/
void	execution(t_vars *vars, t_pipe cmdlst)
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
	call_execve(vars, cmdlst);
}
