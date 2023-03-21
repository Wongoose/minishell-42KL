/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 15:22:35 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/21 21:24:46 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 * Function creates a backup of current pipefd which will be used for the next
 * function, if there is an existing backup, function closes them, then close
 * the current pipefd.
 * 
 * @param index The current command list
 * @param n_cmds Total number of commands
 * @param pipefd The file 
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
