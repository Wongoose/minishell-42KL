#include "minishell.h"

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
void	ft_free_token(t_token *group, int ret)
{
	if (ret == -1)
		return ;
	if (group->left == NULL)
	{
		free(group->value);
		// int	k = -1;
		// dprintf(2, "\n==================\n");
		// while (group->hdoc_str[++k] != NULL)
		// 	dprintf(2, "HDOC[%d]={%s}\n", k, group->hdoc_str[k]);
		// dprintf(2, "\n==================\n");
		if (group->hdoc_str != NULL)
			free_doublearray(group->hdoc_str);
		ft_free_pipe(group->pipe_num, group->cmdlst);
		free(group);
	}
	else if (group->left->left != NULL)
		ft_free_token(group->left, ret);
	else
	{
		ft_free_token(group->left, ret);
		ft_free_token(group->right, ret);
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