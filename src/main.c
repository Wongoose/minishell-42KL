#include "minishell.h"

void	init_vars(t_vars *vars, char **envp)
{
	vars->envp = dup_envp(envp);
	vars->path = ft_split(get_envp_value(vars->envp, "PATH"), ':');
	vars->functions = ft_split("echo cd pwd export unset env exit", ' ');
	vars->last_errno = 0;
	vars->func[E_ECHO] = func_echo;
	vars->func[E_CD] = func_cd;
	vars->func[E_PWD] = func_pwd;
	vars->func[E_EXPORT] = func_export;
	vars->func[E_UNSET] = func_unset;
	vars->func[E_ENV] = func_env;
	vars->func[E_EXIT] = func_exit;
}

int	start_minishell(t_vars *vars, t_token *group)
{
	int	ret;

	if (group->parent == NULL && group->left == NULL)
	{
		return (cmdgroup(vars, group));
	}
	else
	{
		if (group->left->left != NULL)
			start_minishell(vars, group->left);
		else
			ret = cmdgroup(vars, group->left);
		if ((vars->last_errno == 0 && group->operator == 1)
			|| (vars->last_errno == 1 && group->operator == 2))
		{
			if (group->right->left != NULL)
			{
				start_minishell(vars, group->right);
				if ((vars->last_errno == 0 && group->operator == 1)
					|| (vars->last_errno == 1 && group->operator == 2))
					ret = cmdgroup(vars, group->right);
			}
			else
				ret = cmdgroup(vars, group->right);
		}
	}
	return (ret);
}

void	read_terminal(t_vars *vars)
{
	char	*input;

	init_signal();
	input = readline("minihell$> ");
	if (input == NULL) // handles Ctrl-D (Ctrl-D is EOF in terminal which return value of NULL)
	{
		ft_printf("exit\n");
		exit(0);
	}
	if (ft_strlen(input) != 0)
	{
		add_history(input);
		vars->tokens = tokenize_input(vars, input);
		if (vars->tokens == NULL)
			exit(1);
		// print_token_tree(vars->tokens, 0, "ROOT");
		// printf("\n\n");
		if (start_minishell(vars, vars->tokens) == 1)
		{
			;
			/* FREE AND EXIT HERE */
		}
		ft_free(vars);
	}
	free(input);
	usleep(10000);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_vars	vars;

	print_startup();
	init_vars(&vars, envp);
	while (1)
	{
		read_terminal(&vars);
	}
	return (0);
}
