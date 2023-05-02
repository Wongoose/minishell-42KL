#include "minishell.h"

void	init_vars(t_vars *vars, char **envp)
{
	vars->is_subshell = FALSE;
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
		return (cmdgroup(vars, group));
	else
	{
		if (group->left->left != NULL)
			start_minishell(vars, group->left);
		else
			ret = cmdgroup(vars, group->left);
		if ((vars->last_errno == 0 && group->operator == 1)
			|| (vars->last_errno != 0 && group->operator == 2))
		{
			if (group->right->left != NULL)
			{
				start_minishell(vars, group->right);
				if ((vars->last_errno == 0 && group->operator == 1)
					|| (vars->last_errno != 0 && group->operator == 2))
					ret = cmdgroup(vars, group->right);
			}
			else
				ret = cmdgroup(vars, group->right);
		}
	}
	if (vars->is_subshell == FALSE)
		return (ret);
	else
		exit (ret);
}

int	read_terminal(t_vars *vars)
{
	char	*input;
	int		ret;

	ret = -2;
	init_signal();
	input = readline("minihell$> ");
	if (input == NULL)
	{
		printf("exit\n");
		ret = -1;
	}
	else if (ft_strlen(input) != 0)
	{
		add_history(input);
		vars->tokens = tokenize_input(vars, input);
		if (vars->tokens == NULL)
			ret = -1;
		else if (start_minishell(vars, vars->tokens) == 0)
			ret = vars->last_errno;
		ft_free_token(vars->tokens, ret);
	}
	free(input);
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	t_vars	vars;
	int		ret;
	int		exit_status;

	(void)argc;
	(void)argv;
	print_startup();
	init_vars(&vars, envp);
	while (1)
	{
		ret = read_terminal(&vars);
		exit_status = vars.last_errno;
		ft_free_token(vars.tokens, ret);
		if (ret != -2)
			break ;
	}
	ft_free_vars(&vars);
	return (exit_status);
}
