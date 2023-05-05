/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 19:00:06 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/05 17:19:14 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function creates a backup of current pipefd which will be used for the next
 * function, if there is an existing backup, function closes them, then close
 * the current pipefd.
 * 
 * @param index The index of the current command group among the cmd pipe groups
 * @param n_cmds The index of the current command among the pipe group
 * @param pipefd The file descriptor of both the current pipe, and the backup
 * pipe fd before the pipeline
*/
void	ft_close_pipe(int index, int n_cmds, int pipefd[2][2])
{
	if (index != 0)
		close(pipefd[1][0]);
	if (index != n_cmds - 1)
		pipefd[1][0] = pipefd[0][0];
	close(pipefd[0][1]);
	if (index == n_cmds - 1)
		close(pipefd[0][0]);
}

/**
 * dup2 function
 * 
 * @param cmd The current command string
 * @param fd_one The first file descriptor for duping
 * @param fd_two The second file descriptor for duping
 * @return Function does not return
*/
void	ft_dup(char *cmd, int fd_one, int fd_two)
{
	int	ret;

	ret = dup2(fd_one, fd_two);
	if (ret == -1)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 2);
		perror("dup2 failed");
		exit(1);
	}
}

/**
 * Function is called for the last child of the command groups, should call dup2
 * on the STDIN_FILENO and the reading end of the pipe. Function checks for 2
 * other conditions:
 * 1. If redirection exist in current command, call dup2 again for the specific
 *    redirections.
 * 2. If parenthesis exists in current child, call the subshell function
 *    for retokenizaion on the contents in the parenthesis.
 * Otherwise, execute current child with execve.
 * 
 * @param vars The main struct of the program containing the main token trees
 * @param group The current token tree containing its command group
 * @param index The index of the current command among the pipe group
 * @param pipefd The file descriptor of both the current pipe, and the backup
 * pipe fd before the pipeline
 * @return Function does not return
*/
void	last_child(t_vars *vars, t_token *group, int index, int pipefd[2][2])
{
	int	rdr_inout[2];

	ft_dup(group->cmdlst[index].cmd, pipefd[1][0], STDIN_FILENO);
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	ft_dup_inoutfile(index, group->cmdlst[index], group->hdoc_str, rdr_inout);
	if (group->cmdlst[index].has_subshell == TRUE)
		start_subshell(vars, group, group->cmdlst[index], vars->envp);
	else
		execution(vars, &group->cmdlst[index]);
}

/**
 * Middle childs of the command groups, should call dup2 on the STDOUT_FILENO
 * and the writing end of the pipe, also STDIN_FILENO and the reading end of the
 * pipe. Function checks for 2 other conditions:
 * 1. If redirection exist in current command, call dup2 again for the specific
 *    redirections.
 * 2. If parenthesis exists in current child, call the subshell function
 *    for retokenizaion on the contents in the parenthesis.
 * Otherwise, execute current child with execve.
 * 
 * @param vars The main struct of the program containing the main token trees
 * @param group The current token tree containing its command group
 * @param index The index of the current command group among the cmd pipe groups
 * @param pipefd The file descriptor of both the current pipe, and the backup
 * pipe fd before the pipeline
 * @return Function does not return
*/
void	middle_child(t_vars *vars, t_token *group, int index, int pipefd[2][2])
{
	int	rdr_inout[2];

	ft_dup(group->cmdlst[index].cmd, pipefd[0][1], STDOUT_FILENO);
	ft_dup(group->cmdlst[index].cmd, pipefd[1][0], STDIN_FILENO);
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	ft_dup_inoutfile(index, group->cmdlst[index], group->hdoc_str, rdr_inout);
	if (group->cmdlst[index].has_subshell == TRUE)
		start_subshell(vars, group, group->cmdlst[index], vars->envp);
	else
		execution(vars, &group->cmdlst[index]);
}

/**
 * First child of the command groups, should call dup2 on the STDOUT_FILENO and
 * the writing end of the pipe. Function checks for 2 other conditions:
 * 1. If redirection exist in current command, call dup2 again for the specific
 *    redirections.
 * 2. If parenthesis exists in current child, call the subshell function
 *    for retokenizaion on the contents in the parenthesis.
 * Otherwise, execute current child with execve.
 * 
 * @param vars The main struct of the program containing the main token trees
 * @param group The current token tree containing its command group
 * @param index The index of the current command group among the cmd pipe groups
 * @param pipefd The file descriptor of both the current pipe, and the backup
 * pipe fd before the pipeline
 * @return Function does not return
*/
void	first_child(t_vars *vars, t_token *group, int index, int pipefd[2][2])
{
	int	rdr_inout[2];

	ft_dup(group->cmdlst[index].cmd, pipefd[0][1], STDOUT_FILENO);
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	ft_dup_inoutfile(index, group->cmdlst[index], group->hdoc_str, rdr_inout);
	if (group->cmdlst[index].has_subshell == TRUE)
		start_subshell(vars, group, group->cmdlst[index], vars->envp);
	else
		execution(vars, &group->cmdlst[index]);
}
