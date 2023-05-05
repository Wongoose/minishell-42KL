/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_validate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 18:08:31 by zwong             #+#    #+#             */
/*   Updated: 2023/05/05 14:43:31 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**prompt_input(char **tokens)
{
	char	*input;
	char	**new;
	int		i;

	while (1)
	{
		input = validate_raw_input(readline("> "));
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
		return (free_doublearray(tokens), free(input), validate_ops(new));
	}
}

char	**validate_ops(char **tokens)
{
	int		i;

	i = -1;
	while (tokens[++i] != 0)
	{
		if (is_operator(tokens[i]) && tokens[i + 1] == 0)
			tokens = prompt_input(tokens);
		if (tokens == NULL)
			break ;
	}
	return (tokens);
}
