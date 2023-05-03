
#include "minishell.h"

char	*join_str(char *front, char *middle, char *rear)
{
	char	*temp;
	char	*ret;

	if (middle != NULL)
	{
		temp = ft_strjoin(front, middle);
		if (front != NULL)
			free(front);
		free(middle);
	}
	else
		temp = front;
	ret = ft_strjoin(temp, rear);
	if (temp != NULL)
		free(temp);
	if (rear != NULL)
		free(rear);
	return (ret);
}
