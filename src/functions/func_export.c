/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 18:29:10 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/09 22:05:34 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_or_replace(t_vars *vars, char **args)
{
	int		i;
	char	**var_val;

	(void)vars;
	i = 0;
	while (args[++i] != NULL)
	{
		var_val = ft_split(args[i], '=');
		if (verify_variable(var_val[0]))
			return (export_error(1, var_val[0]));
	}
	return (0);
}

int	func_export(t_vars *vars, char **args)
{
	int	ret;

	if (args[1] == NULL || args[1][0] == '#')
		ft_printf("print all exports\n");
	else
	{
		ret = add_or_replace(vars, args);
	}
	return (ret);
}
