/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:19:27 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/10 18:10:56 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_unset_error(int condition, char *var, char *name)
{
	if (condition == 1)
		ft_printf("minishell: export: '%s': not a valid identifier\n", var);
	return (1);
}

t_bool	verify_variable(char *variable)
{
	int	i;

	i = -1;
	while (variable[++i] != 0)
	{
		if (i == 0 && (variable[i] != '_' || !ft_isalpha(variable[i])))
			return (1);
		else if (variable[i] != '_' || ft_isalnum(variable[i]))
			return (1);
	}
	return (0);
}
