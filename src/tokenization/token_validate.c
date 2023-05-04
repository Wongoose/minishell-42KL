/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:08:31 by zwong             #+#    #+#             */
/*   Updated: 2023/05/04 13:07:23 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt_raw_input(char *str)
{
	char	*input;
	char	*result;

	input = readline("> ");
	if (input == NULL)
	{
		free(str);
		return (ft_strdup(""));
	}
	result = join_str(str, NULL, input);
	return (validate_raw_input(result));
	
}

char	*validate_raw_input(char *input)
{
	int		i;
	char	quote_t;
	char	*temp;

	if (input == NULL)
		return (NULL);
	i = -1;
	quote_t = 0;
	while (input[++i])
	{
		if (!quote_t && ft_isquote(input[i]))
			quote_t = input[i];
		else if (quote_t && input[i] == quote_t)
			quote_t = 0;
	}
	temp = ft_trim(ft_strdup(input));
	if (quote_t || (!quote_t && temp[ft_strlen(temp) - 1] == '|'))
		input = prompt_raw_input(input);
	free(temp);
	return (ft_trim(input));
}

char  **prompt_input(char **tokens)
{
	char	*input;
	char	**new_tokens;
	int		i;
	int		j;

	input = readline("> ");
	input = validate_raw_input(input);
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


// NEXT: Deal with parenthesis
// NEXT: Exit prompt when input is NULL Ctrl-D
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
