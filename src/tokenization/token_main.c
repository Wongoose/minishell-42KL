#include "minishell.h"

t_token *create_token(char *value) {
    t_token *new_token = malloc(sizeof(t_token));
    if (!new_token) {
        ft_putstr_fd("Memory allocation failed\n", 2);
        exit(1);
    }
    new_token->left = NULL;
    new_token->right = NULL;
    new_token->value = ft_strdup(value);
    new_token->operator = get_operator_type(value);
    new_token->arguments = ft_split(value, ' ');
    new_token->pipe_list = get_pipe_list(value);
    new_token->pipe_num = get_pipe_num(new_token->pipe_list);
    new_token->exit_status = 0;
    return (new_token);
}

t_token *build_token_tree(char **tokens, int start, int end) {

    int     i;
    int     parens;
    int     precedence;
    int     lowest_precedence_index;
    int     lowest_precedence;
    t_token *new_token;

    if (start > end)
        return NULL;
    
    i = start;
    parens = 0;
    lowest_precedence_index = -1;
    lowest_precedence = INT_MAX;

    while (i <= end)
    {
        if (is_left_paren(tokens[i]))
            parens++;
        else if (is_right_paren(tokens[i]))
            parens--;
        else if (parens == 0 && is_operator(tokens[i]))
        {
            precedence = (ft_strcmp(tokens[i], "&&") == 0) ? 1 : 0;
            if (precedence <= lowest_precedence) {
                lowest_precedence_index = i;
                lowest_precedence = precedence;
            }
        }
        i++;
    }
    if (lowest_precedence_index != -1)
    {
        new_token = create_token(tokens[lowest_precedence_index]);
        new_token->left = build_token_tree(tokens, start, lowest_precedence_index - 1);
        new_token->right = build_token_tree(tokens, lowest_precedence_index + 1, end);
        return (new_token);
    }
    else if (is_left_paren(tokens[start]) && is_right_paren(tokens[end]))
        return (build_token_tree(tokens, start + 1, end - 1));
    else
        return (create_token(tokens[start]));
}

// NEXT: Format code, shorten
// NEXT: Fix leaks
char **format_input(char *input) {
    char    **tokens = malloc(MAX_TOKENS * sizeof(char *));
    char    **split;
    char    *buffer;
    char    *copy;
    int     i;
    int     j;

    // Counting parenthesis
    i = 0;
    j = 0;
    while (input[i] != 0)
    {
        if (input[i] == '(' || input[i] == ')')
            j++;
        i++;
    }
    copy = (char *)malloc(sizeof(char) * (ft_strlen(input) + j + 1));
    // adding spaces between parenthesis and cmds for ft_split later
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
    // Split into char **
    split = ft_split(copy, ' ');
    // Format correctly (e.g. "echo", "z" becomes "echo z")
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
        {
            if (buffer == NULL)
                buffer = ft_strdup(split[i]);
            else
            {
                buffer = ft_strjoin(buffer, ft_strdup(" "));
                buffer = ft_strjoin(buffer, split[i]);
            }
        }
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