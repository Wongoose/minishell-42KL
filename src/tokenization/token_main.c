#include "minishell.h"

char    **validate_tokens(char **tokens);

char  **prompt_input(char **tokens)
{
    char    *input;
    char    **new_tokens;
    int     i;
    int     j;

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
    return (validate_tokens(new_tokens));
}

char    *validate_quote(char *value)
{
    int     quote_level;
    int     i;
    char    quote_type;
    char    *input;

    quote_level = 1;
    i = 0;
    while (value[i])
    {
        if ((!quote_type && (value[i] == '"' || value[i] == '\'')) || value[i] == quote_type)
        {
            quote_type = value[i];
            quote_level *= -1;
        }
        i++;
    }
    if (quote_level == -1)
    {
        input = readline("> ");
        if (ft_strcmp(input, &quote_type) != 0)
            value = ft_strjoin(value, "\n");
        value = ft_strjoin(value, input);
        return (validate_quote(value));
    }
    else
        return (value);
}

char    **validate_tokens(char **tokens)
{
    int paren_level;
    int quote_level;
    int i;

    paren_level = 0;
    quote_level = 1;

    i = -1;
    while (tokens[++i] != 0)
    {
        if (is_left_paren(tokens[i]) && quote_level == 1)
            paren_level++;
        else if (is_right_paren(tokens[i]) && quote_level == 1)
        {
            paren_level--;
			if (paren_level < 0)
			{
                printf("Found unexpected token near '%s'\n", tokens[i]);
                return (NULL);
			}
            if (tokens[i + 1] == 0)
                continue ;
            if (!is_right_paren(tokens[i + 1]) && !is_operator(tokens[i + 1]) && !is_pipe(tokens[i + 1]))
            {
                printf("Found unexpected token near '%s'\n", tokens[i + 1]);
                return (NULL);
            }
        }
        else if (is_operator(tokens[i]) && tokens[i + 1] == 0)
            tokens = prompt_input(tokens);
        else
            tokens[i] = validate_quote(tokens[i]);
    }
    if (quote_level == -1)
        tokens = prompt_input(tokens);
    else if (paren_level > 0)
        tokens = prompt_input(tokens);
    return (tokens);
}

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

    if (ft_strchr(value, '$'))
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
    split = ft_split(copy, ' ');
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