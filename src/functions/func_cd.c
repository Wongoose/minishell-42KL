#include "../../minishell.h"

// NEXT: Do cd with envp variable
int	func_cd(t_vars *vars, char **args)
{
	char	*path;

	if (args[1] == 0) // if no provided path is given, set default to HOME
	{
		path = ms_get_envp_value(vars->envp, "HOME");
		if (path == NULL)
			ft_dprintf(STDERR_FILENO, "HOME not set\n"); // Error if HOME cannot be found
		else if (chdir(path) < 0)
			perror(path);
		free(path);
	}
	else if (chdir(args[1]) < 0)
		perror(args[1]);
	return (0);
}