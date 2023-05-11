/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identifier.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 19:37:23 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/11 15:37:51 by zwong            ###   ########.fr       */
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

int	is_syntax_char(char *input, int i)
{
	return ((input[i] == '|' || input[i] == '&')
		&& (input[i + 1] == 0 || input[i + 1] == ' '));
}
