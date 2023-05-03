/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_handler.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:46:29 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/03 10:28:56 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Function frees heredoc string array.
 * 
 * @param str The heredoc string array
 * @param count The pipe count
 * @return Function does not return
*/
void	ft_free_heredoc(char **str, int count)
{
	int	i;

	i = -1;
	while (++i < count)
	{
		if (str[i] != NULL)
			free(str[i]);
	}
	free(str);
}

/**
 * Since heredocs are handled per command pipe group (if present), function will
 * loop through each and every pipe group and check if the current pipe contains
 * a heredoc. If true, call readline to prompt for input; otherwise, returns
 * " ". We do not return NULL because that is reserved for scenario where
 * SIGQUIT is passed in readline.
 * 
 * @param vars The main struct of the program containing the main token trees
 * @param cmdlst The pipe group
 * @return Returns a string array containing the inputs for heredocs, or returns
 * NULL if SIGQUIT is sent
*/
char	*handle_per_cmdlst(t_vars *vars, t_pipe cmdlst)
{
	int		i;
	char	*ret;

	ret = ft_strdup(" ");
	i = -1;
	while (++i < cmdlst.rdr_count)
	{
		if (cmdlst.rdr_info[i].rdr_type == HEREDOC)
		{
			free(ret);
			ret = get_readline(vars, cmdlst.rdr_info[i].rdr_str);
			if (ret == NULL)
				return (NULL);
		}
	}
	return (ret);
}

/**
 * @brief All heredocs are handled prior to the execution of the program, where
 * function will loop through the command pipe grouop to seek for heredocs,
 * and if found will prompt user for input, then the inputs will be passed to
 * a string array. For example, a command pipe group as follow:
 *      << EOF cmd1 | cmd2 | << EOF cmd3
 * shall return a string array of size pipe_count = 3, whereby the 0th and 3rd
 * index will be initialized based on user inputs (2nd will be set to " "). In
 * any situation where during the prompt for heredoc input, a SIGQUIT signal is
 * sent, the function stops looping to check for heredocs, and instead should
 * stop the execution of the command grouop.
 * 
 * @param vars The main struct of the program containing the main token trees
 * @param group The current token tree containing its command group
 * 
 * @return Returns a string array containing the inputs for heredocs, or returns
 * NULL if SIGQUIT is sent
*/
char	**handle_heredoc(t_vars *vars, t_token *group)
{
	int		i;
	int		ret;
	char	**hdoc_str;

	ret = 0;
	hdoc_str = ft_calloc(group->pipe_num + 1, sizeof(char *));
	i = -1;
	while (++i < group->pipe_num)
	{
		hdoc_str[i] = handle_per_cmdlst(vars, group->cmdlst[i]);
		if (hdoc_str[i] == NULL)
		{
			ret = 1;
			break ;
		}
	}
	if (ret == 1)
		return (ft_free_heredoc(hdoc_str, group->pipe_num), NULL);
	return (hdoc_str);
}
