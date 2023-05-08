#include "minishell.h"

char	update_quote_t(char	quote_t, char value)
{
	if (!quote_t && ft_isquote(value))
		return (value);
	else if (quote_t && value == quote_t)
		return (0);
	return (quote_t);
}