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

char    *add_to_buffer(t_vars *vars, char *buffer, char *value)
{
    char    *tmp;

    if (ft_strchr(value, '$') || ft_strchr(value, '*'))
        value = expand_env_dollar(vars, value);
    tmp = buffer;
    if (tmp == NULL)
        tmp = ft_strdup(value);
    else
    {
        if (value)
            tmp = ft_strjoin(tmp, ft_strdup(" "));
        tmp = ft_strjoin(tmp, value);
        free(buffer);
    }
    return (tmp);
}

// Adding spaces between parenthesis and cmds for ft_split later
// Format correctly (e.g. "echo", "z" becomes "echo z")
char **format_input(t_vars *vars, char *input) {
    char    **tokens = malloc(MAX_TOKENS * sizeof(char *));
    char    **split;
    char    *buffer;
    char    *copy;
    int     i;
    int     j;
    int     paren;

    copy = space_at_paren(input);
    split = split_keep_quotes(copy);
    i = 0;
    j = 0;
    paren = -1;
    buffer = NULL;
    while (split[i] != 0)
    {
        if (is_left_paren(split[i]))
        {
            if (paren == -1)
                paren = 0;
            paren++;
        } 
        else if (is_right_paren(split[i]))   
            paren--;
        if (is_left_paren(split[i]) || is_right_paren(split[i]) || is_operator(split[i]) || (is_pipe(split[i])
            && paren == 0))
        {
            if (buffer)
            {
                tokens[j++] = ft_strdup(buffer);
                free(buffer);
                buffer = NULL;
            }
            tokens[j++] = ft_strdup(split[i++]);
            continue ;
        }
        else
            buffer = add_to_buffer(vars, buffer, split[i++]);
    }
    if (buffer)
    {
        tokens[j++] = ft_strdup(buffer);
        free(buffer);
    }
    tokens[j] = 0;
    return (tokens);
}

t_bool has_pipe_in_shell(char **tokens)
{
    int i;
    int paren;

    i = -1;
    paren = 0;
    while (tokens[++i] != 0)
    {
        if (is_left_paren(tokens[i]))   
            paren++;
        else if (is_right_paren(tokens[i]))   
            paren--;
        if (is_pipe(tokens[i]) && paren == 0)
            return (TRUE);
    }
    return (FALSE);
}

t_token *tokenize_input(t_vars *vars, char *input) {
    int     i;
    char    **tokens;
	t_token *root;

	tokens = format_input(vars, input);
    tokens = validate_tokens(tokens);
    if (!tokens)
	{
    	return (NULL);
	}
	i = 0;
    while (tokens[i] != 0)
		i++;
    if (has_pipe_in_shell(tokens))
        root = create_token(input);
    else
    {
        root = build_token_tree(tokens, 0, i - 1);
    }
	root->parent = NULL;
    free_doublearray(tokens);
    return (root);
}