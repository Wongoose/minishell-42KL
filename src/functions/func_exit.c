/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 15:22:43 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/10 16:23:02 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Each shell command returns an exit code when it terminates, either
 * successfully or unsuccessfully. A status can be used to indicate
 * successful or unsuccessful shell script termination. If status is
 * omitted, the exit status is that of the last command executed.
 * 
 * @param vars main struct
 * @param args arguments for the command, in this case possibly containing
 * the exit status
 * @return The exit command does not return.
*/
int	func_exit(t_vars *vars, char **args)
{
	int	status;

	(void)vars;
	ft_printf("exit\n");
	if (!args[1])
	{
		status = 0;
		// status = struct->exit_status;
	}
	else
		status = ft_atoi(args[1]);
	exit(status);
	return (status);
}
