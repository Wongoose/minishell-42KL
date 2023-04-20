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