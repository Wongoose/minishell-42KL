/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:56:08 by zwong             #+#    #+#             */
/*   Updated: 2023/05/04 12:15:24 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*space_at_paren_and_ops(char *input)
{
	int		i;
	int		j;
	char	*copy;

	i = -1;
	j = 0;
	copy = malloc(ft_strlen(input) + count_paren_and_ops(input) * 2 + 1);
	while (input[++i] != 0)
	{
		if (input[i] == '(' || input[i] == ')' || is_operator_char(input, i))
		{
			copy[j++] = ' ';
			copy[j++] = input[i];
			if (is_operator_char(input, i))
				copy[j++] = input[++i];
			copy[j] = ' ';
		}
		else
			copy[j] = input[i];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

void	append_to_buffer(char **buffer, char *value)
{
	char	*temp;

	temp = ft_strdup(value);
	if (*buffer == NULL)
		*buffer = ft_strdup(temp);
	else if (temp)
		*buffer = join_str(*buffer, ft_strdup(" "), ft_strdup(temp));
	else
		*buffer = ft_strjoin(*buffer, temp);
	free(temp);
}

int	add_to_tokens(char **tokens, char **buffer, int j)
{
	if (*buffer)
	{
		tokens[j++] = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (j);
}

char	**format_input(char **tokens, char *input)
{
	char	**split;
	char	*buffer;
	int		i;
	int		j;
	int		paren;

	split = split_keep_quotes(space_at_paren_and_ops(input));
	i = -1;
	j = 0;
	paren = -1;
	buffer = NULL;
	while (split[++i] != 0)
	{
		paren = update_parenthesis(split[i], paren);
		if (i == find_operator(split, i) && is_operator(split[i]))
		{
			j = add_to_tokens(tokens, &buffer, j);
			tokens[j++] = ft_strdup(split[i]);
		}
		else
			append_to_buffer(&buffer, split[i]);
	}
	tokens[add_to_tokens(tokens, &buffer, j)] = 0;
	free_doublearray(split);
	return (tokens);
}

// NEXT: Simplify validation (missing validation for '|' pipes and quotes)
t_token	*tokenize_input(t_vars *vars, char *input)
{
	int		i;
	char	**tokens;
	t_token	*root;

	tokens = malloc(sizeof(char *) * MAX_TOKENS);
	tokens = format_input(tokens, input);
	tokens = validate_operator(tokens);
	if (!tokens || !tokens[0])
		return (NULL);
	i = 0;
	while (tokens[i] != 0)
		i++;
	if (has_pipe_in_shell(tokens))
		root = create_token(vars, input);
	else
		root = build_token_tree(vars, tokens, 0, i - 1);
	root->parent = NULL;
	free_doublearray(tokens);
	return (root);
}
