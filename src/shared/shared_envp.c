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

char	**dup_envp(char **envp)
{
	int	i;
	int	j;
	char	**new_envp;

	i = 0;
	while (envp[i] != 0)
		i++;
	new_envp = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	j = 0;
	while (envp[i] != 0)
		new_envp[j++] = ft_strdup(envp[i++]);
	return(new_envp);
}