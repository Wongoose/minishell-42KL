#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "minishell.h"

int is_operator(char *token)
{
    return (ft_strcmp(token, "&&") == 0 || ft_strcmp(token, "||") == 0);
}

int is_pipe(char *token)
{
    return (ft_strcmp(token, "|") == 0);
}

int is_left_paren(char *token)
{
    return (ft_strcmp(token, "(") == 0);
}

int is_right_paren(char *token)
{
    return (ft_strcmp(token, ")") == 0);
}

t_operator  get_operator_type(char *value)
{
    if (ft_strcmp(value, "&&") == 0)
        return (AND);
    else if (ft_strcmp(value, "||") == 0)
        return (OR);
    else
        return (UNDEFINED);
}

int count_paren(char *input)
{
    int i;

    i = 0;
    while (*input)
    {
        if (*input == '(' || *input == ')')
            i++;
        input++;
    }
    return (i);
}

// EXTRA
void print_token_tree(t_token *token, int level, char *direction)
{
    if (token == NULL)
    {
        return;
    }

    // Prints the current token with appropriate indentation
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%s: %s\n", direction, token->value);
    print_token_tree(token->left, level + 1, "LEFT");
    print_token_tree(token->right, level + 1, "RIGHT");
}
