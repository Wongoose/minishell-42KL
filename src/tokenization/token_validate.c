/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:08:31 by zwong             #+#    #+#             */
/*   Updated: 2023/05/11 16:17:41 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**prompt_input(t_vars *vars, char **tokens)
{
	char	*input;
	char	**new;
	int		i;

	while (1)
	{
		input = validate_raw_input(vars, readline("> "), TRUE);
		if (input == NULL)
			return (free_doublearray(tokens), NULL);
		if (ft_strlen(input) == 0)
		{
			free(input);
			continue ;
		}
		i = 0;
		while (tokens[i] != 0)
			i++;
		new = ft_calloc(i + 2, sizeof(char *));
		i = -1;
		while (tokens[++i] != 0)
			new[i] = ft_strdup(tokens[i]);
		new[i] = ft_strdup(input);
		return (free_doublearray(tokens), free(input), validate_ops(vars, new));
	}
}

char	**validate_ops(t_vars *vars, char **tokens)
{
	int		i;

	i = -1;
	while (tokens != NULL && tokens[++i] != 0)
	{
		if (i == 0 && (is_pipe(tokens[i]) || ft_strcmp(tokens[i], "&") == 0))
		{
			vars->syntax_err = ft_strdup(tokens[i]);
			free_doublearray(tokens);
			tokens = NULL;
		}
		else if (is_operator(tokens[i]))
		{
			if (tokens[i + 1] == 0)
				tokens = prompt_input(vars, tokens);
			else if (is_operator(tokens[i + 1])
				|| is_pipe(tokens[i + 1]) || ft_strcmp(tokens[i + 1], "&") == 0)
			{
				vars->syntax_err = ft_strdup(tokens[i + 1]);
				free_doublearray(tokens);
				tokens = NULL;
			}
		}
	}
	return (tokens);
}
