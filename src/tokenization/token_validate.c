#include "minishell.h"

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
        if ((!quote_type && ft_isquote(value[i])) || value[i] == quote_type)
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
