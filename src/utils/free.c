#include "minishell.h"


// // NEXT: Extract default free to external function to clear t_pipes
// void	ft_free_tree(t_token *token)
// {
// 	if (token->left == NULL)
// 		ft_free_token(token);
// 	else
// 	{
// 		if (token->left->left != NULL)
// 			ft_free_tree(token->left);
// 		else
// 			ft_free_token(token->left);
// 		if (token->right->left != NULL)
// 			ft_free_tree(token->right);
// 		else
// 			ft_free_token(token->right);

void	ft_free_vars(t_vars *vars)
{
	free_doublearray(vars->envp);
	free_doublearray(vars->path);
	free_doublearray(vars->functions);
}

void	ft_free_pipe(int pipe_num, t_pipe *cmdlst)
{
	int	i;
	int	j;

	i = -1;
	while (++i < pipe_num)
	{
		free(cmdlst[i].cmd);
		if (cmdlst[i].arg != NULL && cmdlst[i].arg[0] != NULL)
			free_doublearray(cmdlst[i].arg);
		j = -1;
		while (++j < cmdlst[i].rdr_count)
			free(cmdlst[i].rdr_info[j].rdr_str);
		if (cmdlst[i].rdr_info != NULL)
			free(cmdlst[i].rdr_info);
	}
	free(cmdlst);
}

// void	ft_free_token(t_token *group)
// {
// 	int	i;

// 	free(group->value);
// 	i = -1;
// 	while (group->hdoc_str != NULL && ++i < group->pipe_num)
// 		if (group->hdoc_str[i] != NULL)
// 			free(group->hdoc_str[i]);
// 	free(group->hdoc_str);
// 	ft_free_pipe(group->pipe_num, group->cmdlst);
// 	free(group);
// 	// int	count;

// 	// if (token->value)
// 	// 	free(token->value);
// 	// count = 0;
// 	// while (count < token->pipe_num)
// 	// {
// 	// 	free_doublearray(token->cmdlst[count].arg);
// 	// 	free(token->cmdlst[count].cmd);
// 	// 	free(token->cmdlst[count].rdr_info);
// 	// 	count++;
// 	// }
// 	// free(token);
// }

/**
 * Main free function, free respective memories depending on ret values.
 * 
 * If ret == -2:
 * Previous commands finish execution, should not free the main struct "vars"
 * and prompt for the next input.
 * 
 * If ret == -1:
 * ctrl-D has been pressed (NULL is sent to readline before tokenization), free
 * only the main struct "vars".
 * 
 * If ret >= 0:
 * "exit" is parsed as a command into readline, free everything
 * 
 * @param tokens The struct containing its command group tree
 * @param ret The return value of previous execution of the token struct
 * 
 * @return Function does not return
*/
void	ft_free_tree(t_token *group, int ret)
{
	int	i;

	if (ret == -1)
		return ;
	if (group->left == NULL)
	{
		free(group->value);
		i = -1;
		while (group->hdoc_str != NULL && ++i < group->pipe_num)
			if (group->hdoc_str[i] != NULL)
				free(group->hdoc_str[i]);
		free(group->hdoc_str);
		ft_free_pipe(group->pipe_num, group->cmdlst);
		free(group);
	}
	else if (group->left->left != NULL)
		ft_free_tree(group->left, ret);
	else
	{
		ft_free_tree(group->left, ret);
		ft_free_tree(group->right, ret);
	}
}

void	free_doublearray(char **data)
{
	int	i;

	i = -1;
	while (data[++i] != NULL)
		free(data[i]);
	free(data);
}