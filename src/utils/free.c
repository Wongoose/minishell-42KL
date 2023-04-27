#include "minishell.h"

void	ft_free(t_vars *vars)
{
	(void)vars;
	// free all tokens link list
}

void	free_doublearray(char **data)
{
	int	i;

	i = -1;
	while (data[++i] != NULL)
		free(data[i]);
	free(data);
}