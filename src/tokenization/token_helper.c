#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "minishell.h"

int is_operator(char *token)
{
    return (ft_strcmp(token, "&&") == 0 || ft_strcmp(token, "||") == 0);
}

int is_left_paren(char *token)
{
    return (ft_strcmp(token, "(") == 0);
}

int is_right_paren(char *token)
{
    return (ft_strcmp(token, ")") == 0);
}

void print_token_tree(t_token *token, int level, char *direction)
{
    if (token == NULL)
    {
        return;
    }

    // Print the current token with appropriate indentation
    for (int i = 0; i < level; i++) {
        printf("    ");
    }
    printf("%s: %s\n", direction, token->value);
    print_token_tree(token->left, level + 1, "LEFT");
    print_token_tree(token->right, level + 1, "RIGHT");
}