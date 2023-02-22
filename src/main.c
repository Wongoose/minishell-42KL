#include "../minishell.h"

// NEXT: Create built-in functions
void	init_vars(t_vars *vars, char **envp)
{
	(void)vars;
	(void)envp;
	vars->functions = ft_split("echo cd pwd export unset env exit", ' ');
	// below are all functino pointers (not yet defin functions)
	// vars->func[MS_ECHO] = ms_echo;
	// vars->func[MS_CD] = ms_cd;
	// vars->func[MS_PWD] = ms_pwd;
	// vars->func[MS_EXPORT] = ms_export;
	// vars->func[MS_UNSET] = ms_unset;
	// vars->func[MS_ENV] = ms_env;
	// vars->func[MS_EXIT] = ms_exit;
}

// NEXT: DO PIPEX
void	ms_read_next_line(t_vars *vars)
{
	// t_cmd	*cmd_list; 
	char	*input;

	ms_init_signal();
	input = readline("$> ");
	if (input == NULL)
		vars->func[MS_EXIT](NULL, NULL);
	// Below is PIPEX
	if (ft_strlen(input) != 0)
	{
		printf(":> %s\n", input);
		// add_history(input);
		// if (!ms_check_dangling(input))
		// {
		// 	cmd_list = ms_get_cmd_list(vars, input);
		// 	if (main->syntax_error == 0)
		// 		ms_run_execution(main, cmd_list);
		// 	else
		// 		g_errno = main->syntax_error;
		// 	ms_cmd_list_free(&cmd_list);
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
		ms_read_next_line(&vars);
	return (0);
	
}
