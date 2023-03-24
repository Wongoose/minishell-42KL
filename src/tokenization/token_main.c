#include "minishell.h"

// t_bool  validate_parenthesis(char *input)
// {

// }

void    space_at_paren(char *copy, char *input)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (input[i] != 0)
    {
        if (input[i] == '(')
        {
            copy[j] = input[i];
            copy[++j] = ' ';
        }
        else if (input[i] == ')')
        {
            copy[j] = ' ';
            copy[++j] = input[i];
        }
        else
            copy[j] = input[i];
        j++;
        i++;
    }
    copy[j] = '\0';
}

char    *add_to_buffer(char *buffer, char *value)
{
    char    *tmp;

    tmp = buffer;
    if (tmp == NULL)
        tmp = ft_strdup(value);
    else
    {
        tmp = ft_strjoin(tmp, ft_strdup(" "));
        tmp = ft_strjoin(tmp, value);
        free(buffer);
    }
    return (tmp);
}

// Adding spaces between parenthesis and cmds for ft_split later
// Format correctly (e.g. "echo", "z" becomes "echo z")
char **format_input(char *input) {
    char    **tokens = malloc(MAX_TOKENS * sizeof(char *));
    char    **split;
    char    *buffer;
    char    *copy;
    int     i;
    int     j;

    // NEXT: Validate input
    copy = (char *)malloc(ft_strlen(input) + count_paren(input) + 1);
    space_at_paren(copy, input);
    split = ft_split(copy, ' ');
    i = 0;
    j = 0;
    buffer = NULL;
    while (split[i] != 0)
    {
        if (is_left_paren(split[i]) || is_right_paren(split[i]) || is_operator(split[i]))
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
            buffer = add_to_buffer(buffer, split[i]);
        i++;
    }
    if (buffer)
    {
        tokens[j++] = ft_strdup(buffer);
        free(buffer);
    }
    tokens[j] = 0;
    return (tokens);
}

t_token *tokenize_input(char *input) {
    char **tokens;
	t_token *root;

	tokens = format_input(input);
    int i = 0;
	while (tokens[i] != 0)
		i++;
    root = build_token_tree(tokens, 0, i - 1);
    free_doublearray(tokens);
    return (root);
}