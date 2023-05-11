/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_operator_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 15:15:06 by zwong             #+#    #+#             */
/*   Updated: 2023/05/11 15:15:18 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_operator	get_operator_type(char *value)
{
	if (ft_strcmp(value, "&&") == 0)
		return (AND);
	else if (ft_strcmp(value, "||") == 0)
		return (OR);
	else
		return (UNDEFINED);
}
