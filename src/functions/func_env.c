#include "../../minishell.h"

int	func_env(t_vars *vars, char **args)
{
	int	i;
	(void)args;

	i = 0;
	while (vars->envp[i] != 0)
	{
		ft_printf("%s\n", vars->envp[i]);
		i++;
	}
	return (0);
}