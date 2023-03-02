#include "../../minishell.h"

char	*get_envp_value(char **envp, char *key)
{
	int		i;
	char	*value;

	i = 0;
	while (envp[i])
	{
		value = ft_strnstr(envp[i], key, ft_strlen(key));
		if (value)
		{
			value += ft_strlen(key);
			value = ft_strdup(value);
			break ;
		}
		i++;
	}
	return (value);
}