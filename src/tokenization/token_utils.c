#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "minishell.h"

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

int		update_parenthesis(char *token, int paren)
{
	if (is_left_paren(token))
    {
        if (paren == -1)
            paren = 0;
        paren++;
    }
	else if (is_right_paren(token))
		paren--;
	return (paren);
}

int should_add_to_tokens(char **token, int i)
{
    printf("\nToken: %s\n", token[i - 1]);
    if (is_pipe(token[i]) && is_right_paren(token[i - 1]))
        printf("\nToken: %d\n", i);
    return (is_left_paren(token[i]) || is_right_paren(token[i]) || is_operator(token[i])
        || (is_pipe(token[i]) && is_right_paren(token[i - 1])));
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
