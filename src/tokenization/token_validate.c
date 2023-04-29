/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:08:31 by zwong             #+#    #+#             */
/*   Updated: 2023/04/28 19:08:43 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char  **prompt_input(char **tokens)
{
	char	*input;
	char	**new_tokens;
	int		i;
	int		j;

	input = readline("> ");
	i = 0;
	j = 0;
	while (tokens[i] != 0)
		i++;
	new_tokens = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (tokens[i] != 0)
		new_tokens[j++] = tokens[i++];
	new_tokens[j++] = ft_strdup(input);
	new_tokens[j] = 0;
	return (validate_operator(new_tokens));
}

char	*validate_quote(char *value)
{
	int		i;
	char	*input;
	char	quote_t;
	int		quote_level;

	quote_level = 1;
	i = 0;
	while (value[i])
	{
		if ((!quote_t && ft_isquote(value[i])) || value[i] == quote_t)
		{
			quote_t = value[i];
			quote_level *= -1;
		}
		i++;
	}
	if (quote_level == -1)
	{
		input = readline("> ");
		// if (ft_strchr(input, quote_t))
		// if (ft_strcmp(input, &quote_t) != 0)
		value  = join_str(ft_strdup(value), ft_strdup("\n"), ft_strdup(input));
		return (validate_quote(value));
	}
	else
		return (value);
}

// char	*validate_paren(char *value)
// {
// 	int		i;
// 	int		paren;
// 	char	*input;
// 	char	**split;

// 	i = 0;
// 	paren = 0;
// 	split = space_at_paren();
// 	while (value[i])
// 	{
// 		if (value[i] == '(')
// 			paren++;
// 		else if (value[i] == ')')
// 		{
// 			paren--;
// 			if (paren < 0)
// 				printf("syntax error near unexpected token '%c'\n", value[i]);
// 			if (value[i + 1] == 0)
// 				continue ;
// 			if (value[i + 1] != ')' && value[i + 1] != )
// 		}
// 	}
// }

// NEXT: Deal with && within prompt_input
char	**validate_operator(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i] != 0)
	{
		if (is_operator(tokens[i]) && tokens[i + 1] == 0)
			tokens = prompt_input(tokens);
		// if (is_left_paren(tokens[i]) && quote_level == 1)
		// 	paren_level++;
		// else if (is_right_paren(tokens[i]) && quote_level == 1)
		// {
		// 	paren_level--;
		// 	if (paren_level < 0)
		// 	{
		// 		printf("Found unexpected token near '%s'\n", tokens[i]);
		// 		return (NULL);
		// 	}
		// 	if (tokens[i + 1] == 0)
		// 		continue ;
		// 	if (!is_right_paren(tokens[i + 1]) && !is_operator(tokens[i + 1]) && !is_pipe(tokens[i + 1]))
		// 	{
		// 		printf("Found unexpected token near '%s'\n", tokens[i + 1]);
		// 		return (NULL);
		// 	}
		// }
		// else
			// tokens[i] = validate_quote(tokens[i]);
	}
	return (tokens);
}
