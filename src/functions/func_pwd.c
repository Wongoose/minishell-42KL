/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:23:11 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/09 18:34:17 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * recreation of the pwd Linux command, where function prints the current
 * working directory path, starting from the root (/).
 * 
 * @param vars main struct (NULL-ed in this case since unused)
 * @param args arguments for the command (NULL-ed in this case since unused)
 * @return The pwd command has 2 exit status: 0 for success; non-zero for
 * failure.
*/
int	func_pwd(t_vars *vars, char **args)
{
	char	*path;

	(void)vars;
	(void)args;
	path = getcwd(NULL, 0);
	if (path == NULL)
		return (1);
	else
	{
		printf("%s\n", path);
		free(path);
		return (0);
	}
}
