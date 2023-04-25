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

int should_add_to_tokens(char **token, int i, int operator_i)
{
    // if (operator_i == -1)
        // return (i != 0 && paren == 0 && (is_pipe(token[i]) && is_right_paren(token[i - 1])));
    if (i == operator_i)
        return (is_operator(token[i]));
    else
        return (0);
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
        if (paren == 0 && is_pipe(tokens[i]))
            return (TRUE);
    }
    return (FALSE);
}

int  find_operator(char **split, int current)
{
    int paren;
    int i;

    paren = 0;
    i = 0;
    while (split[i])
    {
        paren = update_parenthesis(split[i], paren);
        if (paren == 0 && is_operator(split[i]) && current <= i)
            return (i);
        i++;
    }
    return (-1);
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
    printf("%s: %s", direction, token->value);
    int i = 0;
    while (i < token->pipe_num)
    {
        if (token->cmdlst[i++].has_subshell)
        {
            printf("\t[has subshell]");
            break ;
        }
    }
    printf("\n");
    print_token_tree(token->left, level + 1, "LEFT");
    print_token_tree(token->right, level + 1, "RIGHT");
}
