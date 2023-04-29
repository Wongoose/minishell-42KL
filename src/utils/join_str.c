
#include "minishell.h"

char	*join_str(char *front, char *middle, char *rear)
{
	char	*temp;
	char	*ret;

	if (middle != NULL)
	{
		temp = ft_strjoin(front, middle);
		free(front);
		free(middle);
	}
	else
		temp = front;
	ret = ft_strjoin(temp, rear);
	free(temp);
	free(rear);
	return (ret);
}
