/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 18:28:08 by zwong             #+#    #+#             */
/*   Updated: 2023/05/08 18:28:08 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	func_env(t_vars *vars, char **args)
{
	int	i;

	(void)args;
	i = 0;
	while (vars->envp[i] != 0)
	{
		ft_printf("%s\n", vars->envp[i]);
		i++;
	}
	return (0);
}
