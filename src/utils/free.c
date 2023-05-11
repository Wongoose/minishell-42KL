/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:13:37 by zwong             #+#    #+#             */
/*   Updated: 2023/05/04 13:13:37 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_vars(t_vars *vars)
{
	free_doublearray(vars->envp);
	if (vars->path != NULL)
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
		if (cmdlst[i].arg != NULL)
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
void	ft_free_tree(t_token *root, int ret)
{
	int	i;

	if (ret == -1 || root == NULL)
		return ;
	if (root->value == NULL)
		return (free(root));
	ft_free_tree(root->left, ret);
	ft_free_tree(root->right, ret);
	free(root->value);
	if (root->cmdlst != NULL)
	{
		if (root->hdoc_str != NULL)
		{
			i = -1;
			while (++i <= root->pipe_num)
				if (root->hdoc_str[i] != NULL)
					free(root->hdoc_str[i]);
			free(root->hdoc_str);
		}
		ft_free_pipe(root->pipe_num, root->cmdlst);
	}
	free(root);
}

// void	ft_free_tree(t_token *group, int ret, t_bool is_root)
// {
// 	int	i;

// 	if (ret == -1)
// 		return ;
// 	if (group->left == NULL)
// 	{
// 		free(group->value);
// 		// printf("FREED VALUE: %s\n", group->value);
// 		if (group->operator != OR && group->operator != AND)
// 		{
// 			i = -1;
// 			while (group->hdoc_str != NULL && ++i < group->pipe_num)
// 			{
// 				if (group->hdoc_str[i] != NULL)
// 					free(group->hdoc_str[i]);
// 			}
// 			free(group->hdoc_str);
// 			// printf("FREED HDOC_STR\n");
// 			// printf("FREED PIPE\n");
// 			// printf("FREED TOKEN\n");
// 		}
// 		ft_free_pipe(group->pipe_num, group->cmdlst);
// 		free(group);
// 	}
// 	else if (group->left->left != NULL)
// 		ft_free_tree(group->left, ret, FALSE);
// 	else
// 	{
// 		ft_free_tree(group->left, ret, FALSE);
// 		ft_free_tree(group->right, ret, FALSE);
// 	}
// 	if (is_root)
// 	{
// 		group->left = NULL;
// 		ft_free_tree(group, ret, FALSE);
// 	}
// }

void	free_doublearray(char **data)
{
	int	i;

	i = -1;
	while (data[++i] != NULL)
		free(data[i]);
	free(data);
}

void	handle_syntax_err(t_vars *vars)
{
	if (vars->syntax_err != NULL)
	{
		printf("minishell: syntax error near unexpected token `%s'\n",
			vars->syntax_err);
		vars->last_errno = 258;
		free(vars->syntax_err);
	}
}
