#include "minishell.h"

t_pipe	create_new_pipe(char *value)
{
	t_pipe	pipe;
	int		i;
	int		j;
	char	*formatted;
	char	*head;

	formatted = (char *)ft_calloc(ft_strlen(value), 1);
	head = formatted;
	i = 0;
	pipe.has_redirect = FALSE;
	while (value[i] != 0)
	{
		if (value[i] == '>')
		{
			pipe.has_redirect = TRUE;
			pipe.redirect_type = OUT;
			if (value[++i] == '>')
				pipe.redirect_type = APPEND;
			else if (value[i] == ' ')
				i++;
			j = i;
			while (value[j] != 0)
			{
				if (value[j + 1] = ' ')
					pipe.outfile = ft_substr(value, i, j);
			}
			i = j;
		}
		else if (value[i] == '<')
		{
			pipe.has_redirect = TRUE;
			pipe.redirect_type = IN;
			if (value[++i] == '<')
				pipe.redirect_type = HEREDOC;
			else if (value[i] == ' ')
				i++;
			j = i;
			while (value[j] != 0)
			{
				if (value[j + 1] = ' ')
					pipe.infile = ft_substr(value, i, j);
			}
			i = j;
		}
		else
			ft_memset(formatted++, value[i], 1);
		i++;
	}
	free(value);
	pipe.arg = ft_split(head, ' ');
	pipe.cmd = pipe.arg[0];
	return (pipe);
}

t_pipe	*get_pipe_list(char *value)
{
	int		i;
	int		j;
	int		pipe_count;
	t_pipe	*pipe_list;
	char	**args;
	char	*buffer;

	i = 0;
	pipe_count = 0;
	while (value[i] != 0)
	{
		if (value[i] == '|')
			pipe_count++;
		i++;
	}
	if (pipe_count == 0)
		return (NULL);
	pipe_list = (t_pipe *)malloc(sizeof(t_pipe) * (pipe_count + 2));
	buffer = (char *)ft_calloc(1000, 1);
	i = 0;
	j = 0;
	pipe_count = 0;
	while (value[i] != 0)
	{
		if (value[i] == '|')
		{
			if (i == 0)
				ft_printf("minishell: syntax error near unexpected token '|'\n");
			if (buffer[0] != NULL)
			{
				pipe_list[pipe_count++] = create_new_pipe(buffer);
				buffer = (char *)ft_calloc(1000, 1);
				j = 0;
			}
		}
		else
		{
			if (buffer[0] == NULL && value[i] == ' ')
				continue ;
			buffer[j++] = value[i];
		}
		i++;
	}
	if (buffer[0] != NULL)
		pipe_list[pipe_count++] = create_new_pipe(buffer);
	pipe_list[pipe_count] = 0;
	free(buffer);
	return (pipe_list);
}

int	get_pipe_num(t_pipe *pipe_list)
{
	int	i;

	i = 0;
	if (!pipe_list)
		return (0);
	while (pipe_list[i] != 0)
		i++;
	return (i);
}