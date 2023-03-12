#include "../../minishell.h"

static void	find_and_delete(t_vars *vars, char *key)
{
	char	**new_envp;
	char	**split;
	int		i;
	int		j;

	i = 0;
	while (vars->envp[i] != 0)
		i++;
	new_envp = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (vars->envp[i] != 0)
	{
		split = ft_split(vars->envp[i], '=');
		if (ft_strcmp(split[0], key) != 0)
			new_envp[j++] = ft_strdup(vars->envp[i]);
		free_doublearray(split);
		i++;
	}
	free_doublearray(vars->envp);
	vars->envp = new_envp;
}

int	func_unset(t_vars *vars, char **args)
{
	int	i;
	(void)vars;

	i = 1;
	while (args[i] != 0)
	{
		if (validate_unset(args[i]) == FALSE)
			return (export_unset_error(1, args[i], "unset"));
		else
			find_and_delete(vars, args[1]);
		i++;
	}
	i = 0;
	while (vars->envp[i] != 0)
	{
		ft_printf("%s\n", vars->envp[i]);
		i++;
	}
	return (0);
}