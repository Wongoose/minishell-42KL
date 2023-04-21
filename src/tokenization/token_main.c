#include "minishell.h"

char    *space_at_paren(char *input)
{
    int i;
    int j;
    char *copy;

    i = 0;
    j = 0;
    copy = (char *)malloc(ft_strlen(input) + count_paren(input) * 2 + 1);
    while (input[i] != 0)
    {
        if (input[i] == '(' || input[i] == ')')
        {
            copy[j++] = ' ';
            copy[j++] = input[i];
            copy[j] = ' ';
        }
        else
            copy[j] = input[i];
        j++;
        i++;
    }
    copy[j] = '\0';
    return (copy);
}

void    append_to_buffer(t_vars *vars, char **buffer, char *value)
{
    if (ft_strchr(value, '$') || ft_strchr(value, '*'))
        value = expand_env_dollar(vars, value);
    if (*buffer == NULL)
        *buffer = ft_strdup(value);
    else
    {
        if (value)
            *buffer = ft_strjoin(*buffer, " ");
        *buffer = ft_strjoin(*buffer, value);
    }
}

int		add_to_tokens(char **tokens, char **buffer, int j)
{
	if (*buffer)
	{
		tokens[j++] = ft_strdup(*buffer);
		free(*buffer);
		*buffer = NULL;
	}
	return (j);
}

char **format_input(t_vars *vars, char **tokens, char *input) {
    char    **split;
    char    *buffer;
    int     i;
    int     j;
    int     paren;

    split = split_keep_quotes(space_at_paren(input));
    i = -1;
    j = 0;
    paren = -1;
    buffer = NULL;
    while (split[++i] != 0)
    {
        paren = update_parenthesis(split[i], paren);
        if (should_add_to_tokens(split, i, find_operator(split)))
        {
            j = add_to_tokens(tokens, &buffer, j);
	        tokens[j++] = ft_strdup(split[i]);
        }
        else
            append_to_buffer(vars, &buffer, split[i]);
    }
    j = add_to_tokens(tokens, &buffer, j);
    tokens[j] = 0;
    free_doublearray(split);
    return (tokens);
}

t_token *tokenize_input(t_vars *vars, char *input) {
    int     i;
    char    **tokens;
	t_token *root;

    input = ft_trim_paren(input);
    tokens = malloc(sizeof(char *) * MAX_TOKENS);
	tokens = format_input(vars, tokens, input);
    tokens = validate_tokens(tokens);
    if (!tokens)
    	return (NULL);
	i = 0;
    while (tokens[i] != 0)
		i++;
    if (has_pipe_in_shell(tokens))
        root = create_token(input);
    else
        root = build_token_tree(tokens, 0, i - 1);
	root->parent = NULL;
    free_doublearray(tokens);
    return (root);
}
