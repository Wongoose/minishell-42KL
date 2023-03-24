#include "minishell.h"

int	count_pipes(char *value)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (value[i] != 0)
	{
		if (value[i] == '|')
			count++;
		i++;
	}
	return (count);
}

void	print_pipe_info(t_pipe pipe)
{
	int	i;

	i = 0;
	printf("RDR_COUNT is: %d\n", pipe.rdr_count);
	while (i < pipe.rdr_count)
	{
		printf("INFO %d: %s", i, pipe.rdr_info[i].rdr_str);
		if (pipe.rdr_info[i].rdr_type == IN)
			printf(", IN\n\n");
		else if (pipe.rdr_info[i].rdr_type == OUT)
			printf(", OUT\n\n");
		else if (pipe.rdr_info[i].rdr_type == APPEND)
			printf(", APPEND\n\n");
		else if (pipe.rdr_info[i].rdr_type == HEREDOC)
			printf(", HEREDOC\n\n");
		i++;
	}
}

int	handle_rdr_out(int i, char *value, t_rdrinfo *rdr_info)
{
	int	j;

	rdr_info->rdr_type = OUT;
	if (value[++i] == '>')
	{
		rdr_info->rdr_type = APPEND;
		i++;
	}
	while (value[i] == ' ')
		i++;
	j = i;
	while (value[j] != 0)
	{
		if (value[j + 1] == ' ' || value[j + 1] == '\0')
		{
			if (rdr_info->rdr_str)
				free(rdr_info->rdr_str);
			rdr_info->rdr_str = ft_substr(value, i, j++ - i + 1);
			// Handle error: [echo > >>> outfile] (refer to bash)
			break ;
		}
		j++;
	}
	return (j);
}

int	handle_rdr_in(int i, char *value, t_rdrinfo *rdr_info)
{
	int	j;

	rdr_info->rdr_type = IN;
	if (value[++i] == '<')
	{
		rdr_info->rdr_type = HEREDOC;
		i++;
	}
	while (value[i] == ' ')
		i++;
	j = i;
	while (value[j] != 0)
	{
		if (value[j + 1] == ' ' || value[j + 1] == '\0')
		{
			if (rdr_info->rdr_str)
				free(rdr_info->rdr_str);
			rdr_info->rdr_str = ft_substr(value, i, j++ - i + 1);
			break ;
		}
		j++;
	}
	return (j);
}