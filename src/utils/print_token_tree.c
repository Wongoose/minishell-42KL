/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_token_tree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 12:13:05 by zwong             #+#    #+#             */
/*   Updated: 2023/05/09 12:13:27 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_token_tree(t_token *token, int level, char *direction)
{
	int	i;

	if (token == NULL)
		return ;
	i = -1;
	while (++i < level)
		printf("    ");
	printf("%s: %s", direction, token->value);
	i = 0;
	while (i < token->pipe_num)
	{
		if (token->cmdlst[i++].has_subshell)
		{
			printf("\t[has subshell]");
			break ;
		}
	}
	printf("\n");
	print_token_tree(token->left, level + 1, "LEFT");
	print_token_tree(token->right, level + 1, "RIGHT");
}
