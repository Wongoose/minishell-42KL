/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:22:35 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/04 22:49:57 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * As the name of the function suggests, this is a error message printer.
 * 
 * @param cmd The command string of the current command group
 * @param str Error message
 * 
 * @return Function returns error (1)
*/
int	error(char *cmd, char *str)
{
	if (cmd != NULL)
		printf("%s: %s\n", cmd, str);
	else
		printf("%s\n", str);
	return (1);
}

/**
 * Function writes the i-th index of the heredoc string array into a file
 * descriptor.
 * 
 * @param i The index of the current command group among the cmd pipe groups,
 * also used to extract the string from the heredoc using the same index.
 * @param hdoc Heredoc string array prompted at the start of the
 * piping/execution program
 * 
 * @return Function returns a file descriptor containing a string passed from
 * the heredoc of the i-th index
*/
int	do_heredoc(int i, char **hdoc)
{
	int	fd[2];

	if (pipe(fd) == -1)
		exit(error(NULL, "Heredoc: pipe failed"));
	write(fd[1], hdoc[i], ft_strlen(hdoc[i]));
	close(fd[1]);
	return (fd[0]);
}

/**
 * Function calls open() system call that will return a file descriptor to the
 * opened entry. The 2 if statements are used when input (IN/HEREDOC) or output
 * (OUT/APPEND) redirections exist in the current command group.
 * 
 * @param i The index of the current command group among the cmd pipe groups
 * @param info The redirection info struct of the current command group
 * @param hdoc Heredoc string array prompted at the start of the
 * piping/execution program
 * @param rdr_inout The file descriptor of the last input/output redirections
 * 
 * @return Function does not return
*/
void	ft_open(int i, t_rdrinfo info, char **hdoc, int rdr_inout[2])
{
	if ((info.rdr_type == IN || info.rdr_type == HEREDOC))
	{
		if (rdr_inout[0] != -42)
			close(rdr_inout[0]);
		if (info.rdr_type == IN)
			rdr_inout[0] = open(info.rdr_str, O_RDONLY);
		else if (info.rdr_type == HEREDOC)
			rdr_inout[0] = do_heredoc(i, hdoc);
		if (rdr_inout[0] == -1)
			exit(error(info.rdr_str, "No such file or directory"));
	}
	else if ((info.rdr_type == OUT || info.rdr_type == APPEND))
	{
		if (rdr_inout[1] != -42)
			close(rdr_inout[1]);
		if (info.rdr_type == OUT)
			rdr_inout[1] = open(info.rdr_str, O_CREAT | O_TRUNC | O_RDWR,
					S_IRWXU | S_IRGRP | S_IROTH);
		else if (info.rdr_type == APPEND)
			rdr_inout[1] = open(info.rdr_str, O_CREAT | O_APPEND | O_RDWR,
					S_IRWXU | S_IRGRP | S_IROTH);
		if (rdr_inout[1] == -1)
			exit(error(info.rdr_str, "No such file or directory"));
	}
}

/**
 * Function checks if redirection exists in current command group. It is
 * possible for a command group to have multiple input/output redirections
 * (Example: < infile1 < infile2 cmd > outfile1 > outfile2), hence a loop is
 * required to open all files related to the redirections. However, only the
 * last redirection will be stored and dup with current io stream (which may
 * be dupped to a pipe if multiple command groups across pipelines exist).
 * 
 * @param i The index of the current command group among the cmd pipe groups
 * @param cmdlst The struct containing information of current command group,
 * including command and arguments, redirections, etc.
 * @param hdoc Heredoc string array prompted at the start of the
 * piping/execution program
 * @param rdr_inout The file descriptor of the last input/output redirections
 * 
 * @return Function does not return
*/
void	ft_dup_inoutfile(int i, t_pipe cmdlst, char **hdoc, int rdr_inout[2])
{
	int	j;

	rdr_inout[0] = -42;
	rdr_inout[1] = -42;
	j = -1;
	while (++j < cmdlst.rdr_count)
		ft_open(i, cmdlst.rdr_info[j], hdoc, rdr_inout);
	if (rdr_inout[0] != -42)
		ft_dup("infile", rdr_inout[0], STDIN_FILENO);
	if (rdr_inout[1] != -42)
		ft_dup("outfile", rdr_inout[1], STDOUT_FILENO);
	close(rdr_inout[0]);
	close(rdr_inout[1]);
}
