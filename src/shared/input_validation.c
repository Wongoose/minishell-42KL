/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:14:38 by zwong             #+#    #+#             */
/*   Updated: 2023/05/11 16:25:53 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_str(char *input, int start)
{
	int	end;

	end = start;
	while (input[end] != ' ' && input[end])
		end++;
	return (ft_substr(input, start, end - start));
}

char	*prompt_raw_input(t_vars *vars, char *str)
{
	char	*input;
	char	*result;

	input = readline("> ");
	if (input == NULL)
	{
		free(str);
		return (ft_strdup(""));
	}
	if (ft_strlen(input) == 1 && is_syntax_char(input, 0))
	{
		add_history(str);
		return (vars->syntax_err
			= ft_substr(input, 0, 1), free(str), free(input), ft_strdup(""));
	}
	result = join_str(str, NULL, input);
	return (validate_raw_input(vars, result, FALSE));
}

int	validate_op_cases(t_vars *vars, char *input, int i, t_bool from_op)
{
	int	j;

	if (is_operator_char(input, i))
	{
		if (!from_op)
		{
			j = i;
			while (j > 0 && input[j - 1] == ' ' && input[j - 1])
				j--;
			if (j == 0 || input[j - 1] == '(')
				return (vars->syntax_err = get_str(input, i), -1);
		}
		i++;
		while (input[i + 1] == ' ')
			i++;
		if (is_syntax_char(input, i + 1))
			return (vars->syntax_err = get_str(input, i + 1), -1);
	}
	return (0);
}

int	validate_paren(t_vars *vars, char *input, int i, int *paren)
{
	if (input[i] == '(')
	{
		(*paren)++;
		while (input[i + 1] == ' ')
			i++;
		if (input[i + 1] == '\0')
			return (0);
		if (input[i + 1] == '|' || input[i + 1] == '&')
			return (vars->syntax_err = ft_substr(input, i + 1, 1), -1);
	}
	else if (input[i] == ')')
	{
		(*paren)--;
		if (*paren < 0)
			return (vars->syntax_err = ft_strdup(")"), -1);
		while (input[i + 1] == ' ')
			i++;
		if (input[i + 1] == '\0')
			return (0);
		if (input[i + 1] != ')' && input[i + 1] != '|'
			&& !is_operator_char(input, i + 1) && !is_rdr_char(input[i + 1]))
			return (vars->syntax_err = get_str(input, i + 1), -1);
	}
	return (0);
}

char	*validate_raw_input(t_vars *vars, char *input, t_bool from_op)
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
		if (!quote_t && (validate_paren(vars, input, i, &paren) == -1
				|| validate_op_cases(vars, input, i, from_op) == -1))
			return (add_history(input), free(input), ft_strdup(""));
	}
	temp = ft_trim(ft_strdup(input));
	if (quote_t || (!quote_t && (temp[ft_strlen(temp) - 1] == '|'
				&& ft_strlen(temp) != 1
				&& temp[ft_strlen(temp) - 2] != '|')) || paren > 0)
		input = prompt_raw_input(vars, input);
	return (free(temp), ft_trim(input));
}
