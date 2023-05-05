/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 17:59:43 by zwong             #+#    #+#             */
/*   Updated: 2023/05/05 16:44:59 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_token	*create_token(t_vars *vars, char *value)
{
	t_token	*new_token;
	char	*formatted;

	(void)vars;
	new_token = malloc(sizeof(t_token));
	if (!new_token)
		exit(1);
	if (value == NULL)
		return (new_token);
	formatted = ft_strdup(value);
	new_token->left = NULL;
	new_token->right = NULL;
	new_token->value = formatted;
	new_token->operator = get_operator_type(formatted);
	new_token->pipe_num = 0;
	new_token->hdoc_str = NULL;
	if (is_operator(formatted))
		new_token->cmdlst = NULL;
	else
		new_token->cmdlst = generate_pipe_list(formatted, new_token);
	new_token->exit_status = 0;
	return (new_token);
}

int	find_lowest_precedence(char **tokens, int start, int end)
{
	int	i;
	int	parens;
	int	lowest_precedence_i;

	i = end;
	parens = 0;
	lowest_precedence_i = -1;
	while (i >= start)
	{
		if (is_right_paren(tokens[i]))
			parens++;
		else if (is_left_paren(tokens[i]))
			parens--;
		else if (parens == 0 && is_operator(tokens[i]))
		{
			if (lowest_precedence_i == -1)
				lowest_precedence_i = i;
		}
		i--;
	}
	return (lowest_precedence_i);
}

int	is_balanced(char **tokens, int start, int end)
{
	int	parens;
	int	i;

	if (!is_left_paren(tokens[start]) || !is_right_paren(tokens[end]))
		return (0);
	parens = 0;
	i = start;
	while (i <= end)
	{
		if (is_left_paren(tokens[i]))
			parens++;
		else if (is_right_paren(tokens[i]))
			parens--;
		if (parens < 0)
			return (0);
		i++;
	}
	return (parens == 0);
}

t_token	*build_token_tree(t_vars *vars, char **tokens, int start, int end)
{
	int		lowest_prec_i;
	t_token	*token;

	if (start > end)
		return (NULL);
	lowest_prec_i = find_lowest_precedence(tokens, start, end);
	if (lowest_prec_i != -1)
	{
		token = create_token(vars, tokens[lowest_prec_i]);
		token->left = build_token_tree(vars, tokens, start, lowest_prec_i - 1);
		token->right = build_token_tree(vars, tokens, lowest_prec_i + 1, end);
		return (token);
	}
	else if (is_balanced(tokens, start, end))
		return (build_token_tree(vars, tokens, start + 1, end - 1));
	else
		return (create_token(vars, tokens[start]));
}
