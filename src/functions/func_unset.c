#include "minishell.h"

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
	int	ret;

	i = 1;
	ret = 0;
	while (args[i] != 0)
	{
		if (verify_variable(args[i]) == FALSE)
			ret = export_unset_error(1, args[i], "unset");
		else if (ft_strcmp(args[i], "_") == 0)
			continue ;
		else
			find_and_delete(vars, args[i]);
		i++;
	}
	return (ret);
}
