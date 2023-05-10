/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:06:17 by zwong             #+#    #+#             */
/*   Updated: 2023/05/10 13:59:57 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_paren_and_ops(char *input)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '(' || input[i] == ')')
			count++;
		else if (is_operator_char(input, i))
		{
			i++;
			count++;
		}
		i++;
	}
	return (count);
}

int	update_parenthesis(char *token, int paren)
{
	if (is_left_paren(token))
	{
		if (paren == -1)
			paren = 0;
		paren++;
	}
	else if (is_right_paren(token))
		paren--;
	return (paren);
}

t_bool	is_operator_char(char *input, int i)
{
	if (input[i + 1] == 0)
		return (0);
	else
		return ((input[i] == '&' && input[i + 1] == '&')
			|| (input[i] == '|' && input[i + 1] == '|'));
}

// int	should_add_to_tokens(char **token, int i, int operator_i)
// {
// 	if (i == operator_i)
// 		return (is_operator(token[i]));
// 	else
// 		return (0);
// }

t_bool	has_pipe_in_shell(char **tokens)
{
	int	i;
	int	paren;

	i = -1;
	paren = 0;
	while (tokens[++i] != 0)
	{
		if (is_left_paren(tokens[i]))
			paren++;
		else if (is_right_paren(tokens[i]))
			paren--;
		if (paren == 0 && (is_pipe(tokens[i]) || is_rdr_str(tokens[i])))
			return (TRUE);
	}
	return (FALSE);
}

int	find_operator(char **split, int current)
{
	int	paren;
	int	i;

	paren = 0;
	i = 0;
	while (split[i])
	{
		paren = update_parenthesis(split[i], paren);
		if (paren == 0 && is_operator(split[i]) && current <= i)
			return (i);
		i++;
	}
	return (-1);
}
