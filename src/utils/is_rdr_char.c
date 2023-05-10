#include "minishell.h"

t_bool	is_rdr_char(char value)
{
	return (value == '>' || value == '<');
}

t_bool	is_rdr_str(char *value)
{
	return (ft_strcmp(value, ">") == 0 || ft_strcmp(value, ">>") == 0
		|| ft_strcmp(value, "<") == 0 || ft_strcmp(value, "<<") == 0);
}