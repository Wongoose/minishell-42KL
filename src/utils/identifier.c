/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:37:23 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/05 19:37:25 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char *token)
{
	return (ft_strcmp(token, "&&") == 0 || ft_strcmp(token, "||") == 0);
}

int	is_pipe(char *token)
{
	return (ft_strcmp(token, "|") == 0);
}

int	is_left_paren(char *token)
{
	return (ft_strcmp(token, "(") == 0);
}

int	is_right_paren(char *token)
{
	return (ft_strcmp(token, ")") == 0);
}

t_operator	get_operator_type(char *value)
{
	if (ft_strcmp(value, "&&") == 0)
		return (AND);
	else if (ft_strcmp(value, "||") == 0)
		return (OR);
	else
		return (UNDEFINED);
}
