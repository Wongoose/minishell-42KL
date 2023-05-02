#include "minishell.h"

void	ft_free_token(t_token *token)
{
	int	count;

	if (token->value)
		free(token->value);
	count = 0;
	while (count < token->pipe_num)
	{
		free_doublearray(token->cmdlst[count].arg);
		free(token->cmdlst[count].cmd);
		free(token->cmdlst[count].rdr_info);
		count++;
	}
	free(token);
}

// NEXT: Extract default free to external function to clear t_pipes
void	ft_free_tree(t_token *token)
{
	if (token->left == NULL)
		ft_free_token(token);
	else
	{
		if (token->left->left != NULL)
			ft_free_tree(token->left);
		else
			ft_free_token(token->left);
		if (token->right->left != NULL)
			ft_free_tree(token->right);
		else
			ft_free_token(token->right);
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