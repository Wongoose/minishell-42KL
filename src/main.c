#include "minishell.h"

// NEXT: Create built-in functions
void	init_vars(t_vars *vars, char **envp)
{
	vars->envp = dup_envp(envp);
	vars->path = ft_split(get_envp_value(vars->envp, "PATH"), ':');
	vars->functions = ft_split("echo cd pwd export unset env exit", ' ');
	// below are all function pointers (not yet define functions)
	vars->func[E_ECHO] = func_echo;
	vars->func[E_CD] = func_cd;
	vars->func[E_PWD] = func_pwd;
	vars->func[E_EXPORT] = func_export;
	vars->func[E_UNSET] = func_unset;
	vars->func[E_ENV] = func_env;
	vars->func[E_EXIT] = func_exit;
}

//
// static t_cmd	*ms_get_cmd_list(t_main *main, char *input)
// {
// 	t_parser	*parser;
// 	t_cmd		*cmd_list;

// 	parser = ms_parser_init(ms_lexer_init(ft_strdup(input)));
// 	cmd_list = ms_parser_parse_cmd_list(parser);
// 	main->syntax_error = parser->syntax_error;
// 	ms_parser_free(&parser);
// 	return (cmd_list);
// }

// static void	ms_run_execution(t_main *main, t_cmd *cmd_list)
// {
// 	t_exe	*exec;

// 	exec = ms_executor_init();
// 	ms_hd_cmd_queue(exec, cmd_list, EQ);
// 	ms_executor_cmd_list(main, exec, cmd_list);
// 	ms_executor_free(&exec);
// }

// int	start_left(t_vars *vars, t_token *left_group)
// {
// 	int	result;

// 	if (left_group->left != NULL)
// 		start_left(vars, left_group->left);
// 	else
// 	{
// 		result = cmdgroup(vars, left_group);
// 		if ()
// 	}
// }

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

// NEXT: DO PIPEX
void	read_terminal(t_vars *vars)
{
	char	*input;
	// char	**test_args;

	init_signal();
	input = readline("minihell$> ");
	if (input == NULL) // handles Ctrl-D (Ctrl-D is EOF in terminal which return value of NULL)
	{
		ft_printf("exit\n");
		exit(0);
	}
	// Below is PIPEX
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
		// TEST CODE >>>
		// test_args = ft_split(input, ' ');
		// if (cmdgroup(vars, &(vars->tokens[0])) == 1)
		// {
		// 	;
		// 	/* FREE AND EXIT HERE */
		// }
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
