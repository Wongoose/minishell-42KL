#include "minishell.h"

t_pipe	create_new_pipe(char *value)
{
	t_pipe	pipe;
	int		i;
	int		j;
	int		rdr_i;
	char	*formatted;
	char	*head;
	
	formatted = (char *)ft_calloc(ft_strlen(value), 1);
	pipe.rdr_list = (t_redirect *)ft_calloc(1000, sizeof(t_redirect));
	head = formatted;
	i = 0;
	rdr_i = 0;
	printf("\n=====\n\nCreating new pipe for: %s\n", value);
	while (value[i] != 0)
	{
		if (value[i] == '>')
		{
			pipe.rdr_list[rdr_i] = OUT;
			if (value[++i] == '>')
				pipe.rdr_list[rdr_i] = APPEND;
			else if (value[i] == ' ')
				i++;
			rdr_i++;
			j = i;
			while (value[j] != 0)
			{
				if (value[j + 1] == ' ')
				{
					if (pipe.outfile)
						free(pipe.outfile);
					pipe.outfile = ft_substr(value, i, j++ - i + 1);
					break ;
				}
				j++;
			}
			i = j;
		}
		else if (value[i] == '<')
		{
			pipe.rdr_list[rdr_i] = IN;
			if (value[++i] == '<')
				pipe.rdr_list[rdr_i] = HEREDOC;
			else if (value[i] == ' ')
				i++;
			rdr_i++;
			j = i;
			while (value[j] != 0)
			{
				if (value[j + 1] == ' ')
				{
					if (pipe.rdr_list[rdr_i] == HEREDOC)
					{
						if (pipe.delim)
							free(pipe.delim);
						pipe.delim = ft_substr(value, i, j++ - i + 1);
					}
					else
					{
						if (pipe.infile)
							free(pipe.infile);
						pipe.infile = ft_substr(value, i, j++ - i + 1);
					}
					break ;
				}
				j++;
			}
			i = j;
		}
		else
		{
			ft_memset(formatted++, value[i], 1);
		}
		i++;
	}
	pipe.arg = ft_split(head, ' ');
	pipe.cmd = pipe.arg[0];
	printf("=NEW PIPE: '%s', '%s', '%s'\n", pipe.cmd, pipe.arg[1], pipe.arg[2]);
	return (pipe);
}

t_pipe	*generate_pipe_list(char *value, t_token *token)
{
	int		i;
	int		j;
	int		pipe_count;
	t_pipe	*pipe_list;
	char	*buffer;

	if (is_operator(value))
		return (NULL);
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
	pipe_list = (t_pipe *)malloc(sizeof(t_pipe) * (pipe_count + 1));
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
			if (buffer[0] != 0)
			{
				pipe_list[pipe_count++] = create_new_pipe(buffer);
				buffer = (char *)ft_calloc(1000, 1);
				j = 0;
			}
		}
		else
		{
			if (buffer[0] == 0 && value[i] == ' ')
			{
				i++;
				continue ;
			}
			buffer[j++] = value[i];
		}
		i++;
	}
	if (buffer[0] != 0)
		pipe_list[pipe_count] = create_new_pipe(buffer);
	token->pipe_num = pipe_count;
	free(buffer);
	return (pipe_list);
}
