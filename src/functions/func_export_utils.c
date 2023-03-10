/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_export_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:19:27 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/10 17:17:34 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_unset_error(int condition, char *var, char *name)
{
	if (condition == 1)
		ft_printf("minishell: %s: '%s': not a valid identifier\n", name, var);
	return (1);
}

t_bool	verify_variable(char *variable)
{
	int	i;

	i = -1;
	while (variable[++i] != 0)
	{
		if (i == 0 && (variable[i] != '_' || !ft_isalpha(variable[i])))
			return (FALSE);
		else if (variable[i] != '_' || ft_isalnum(variable[i]))
			return (FALSE);
	}
	return (TRUE);
}

t_bool	validate_unset(char *variable)
{
	int	i;

	i = -1;
	if (ft_isalpha(variable[++i]) == 0)
		return (FALSE);
	while (variable[++i] != '\0')
	{
		if (ft_isalnum(variable[i]) == 0)
			return (FALSE);
	}
	return (TRUE);
}