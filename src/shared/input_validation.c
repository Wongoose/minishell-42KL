/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:14:38 by zwong             #+#    #+#             */
/*   Updated: 2023/05/05 14:47:11 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_str(char *input, int start)
{
	int	end;

	end = start;
	while (input[end] != ' ' && input[end])
		end++;
	return (ft_substr(input, start, end - start));
}

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

int	validate_paren(char quote_t, char *input, int i, int *paren)
{
	if (quote_t)
		return (0);
	if (input[i] == '(')
		(*paren)++;
	else if (input[i] == ')')
	{
		(*paren)--;
		if (*paren < 0)
			return (printf("Found unexpected token near '%c'\n", input[i]), -1);
		while (input[i + 1] == ' ')
			i++;
		if (input[i + 1] == '\0')
			return (0);
		if (input[i + 1] != ')' && input[i + 1] != '|'
			&& !is_operator_char(input, i + 1))
			return (printf("Found unexpected token near '%s'\n",
					get_str(input, i + 1)), -1);
	}
	return (0);
}

char	*validate_raw_input(char *input)
{
	int		i;
	int		paren;
	char	quote_t;
	char	*temp;

	if (input == NULL)
		return (NULL);
	i = -1;
	paren = 0;
	quote_t = 0;
	while (input[++i])
	{
		quote_t = update_quote_t(quote_t, input[i]);
		if (validate_paren(quote_t, input, i, &paren) == -1)
			return (add_history(input), free(input), ft_strdup(""));
	}
	temp = ft_trim(ft_strdup(input));
	if (quote_t || (!quote_t && temp[ft_strlen(temp) - 1] == '|') || paren > 0)
		input = prompt_raw_input(input);
	return (free(temp), ft_trim(input));
}
