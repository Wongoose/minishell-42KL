/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:22:36 by zwong             #+#    #+#             */
/*   Updated: 2023/05/04 13:22:36 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_vars(t_vars *vars, char **envp)
{
	vars->tokens = NULL;
	vars->is_subshell = FALSE;
	vars->envp = dup_envp(envp);
	vars->path = ft_split(get_envp_value(vars->envp, ft_strdup("PATH")), ':');
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

void	recurse_start(int *ret, t_vars *vars, t_token *group)
{
	if (group->left->left != NULL)
		start_minishell(vars, group->left);
	else
		*(ret) = cmdgroup(vars, group->left);
	if ((vars->last_errno == 0 && group->operator == AND)
		|| (vars->last_errno != 0 && group->operator == OR))
	{
		if (group->right->left != NULL)
		{
			start_minishell(vars, group->right);
			if ((vars->last_errno == 0 && group->operator == AND)
				|| (vars->last_errno != 0 && group->operator == OR))
				*(ret) = cmdgroup(vars, group->right);
		}
		else
			*(ret) = cmdgroup(vars, group->right);
	}
}

int	start_minishell(t_vars *vars, t_token *group)
{
	int	ret;

	if (group->parent == NULL && group->left == NULL)
		return (cmdgroup(vars, group));
	else
		recurse_start(&ret, vars, group);
	if (vars->is_subshell == FALSE)
		return (ret);
	else
		exit (vars->last_errno);
}

int	read_terminal(t_vars *vars)
{
	char	*input;
	int		ret;

	ret = -2;
	init_signal();
	input = readline("minihell$> ");
	input = validate_raw_input(input);
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
		vars.tokens = NULL;
		ret = read_terminal(&vars);
		exit_status = vars.last_errno;
		ft_free_tree(vars.tokens, ret);
		if (ret != -2)
			break ;
	}
	ft_free_vars(&vars);
	return (exit_status);
}
