#include "../../minishell.h"

int	func_cd(t_vars *vars, char **args)
{
	char	*path;

	(void)args;

	if (args[1] == 0) // if no provided path is given, set default to HOME
	{
		path = get_envp_value(vars->envp, "HOME");
		if (path == NULL)
			ft_putstr_fd("HOME not set\n", STDERR_FILENO); // Error if HOME cannot be found
		else if (chdir(path) < 0) // chdir is a system function
			perror(path);
		free(path);
	}
	else if (chdir(args[1]) < 0)
		perror(args[1]);
	return (0);
}