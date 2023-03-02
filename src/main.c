#include "../minishell.h"

// NEXT: Create built-in functions
void	init_vars(t_vars *vars, char **envp)
{
	vars->envp = envp;
	vars->functions = ft_split("echo cd pwd export unset env exit", ' ');
	// below are all function pointers (not yet define functions)
	vars->func[E_ECHO] = func_echo;
	vars->func[E_CD] = func_cd;
	// vars->func[MS_PWD] = ms_pwd;
	// vars->func[MS_EXPORT] = ms_export;
	// vars->func[MS_UNSET] = ms_unset;
	// vars->func[MS_ENV] = ms_env;
	// vars->func[MS_EXIT] = ms_exit;
}

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

// NEXT: DO PIPEX
void	read_terminal(t_vars *vars)
{
	// t_cmd	*cmd_list;
	char	*input;
	(void)vars;

	init_signal();
	input = readline("$> ");
	if (input == NULL) // handles Ctrl-D (Ctrl-D is EOF in terminal which return value of NULL)
	{
		ft_printf("exit");
		exit(1);
	}
	// Below is PIPEX
	if (ft_strlen(input) != 0)
	{
		printf(":> %s\n", input);
		add_history(input);
		// if (!ms_check_dangling(input))
		// {
		// cmd_list = ms_get_cmd_list(vars, input); 
		// ms_run_execution(main, cmd_list);
		// ms_cmd_list_free(&cmd_list);
		// }
	}
	free(input);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	t_vars	vars;

	init_vars(&vars, envp);
	while (1)
		read_terminal(&vars);
	return (0);
}
