#include "../../minishell.h"

/**
 * Function gets the value of the environment variable.
 * 
 * @param envp The environment variable array
 * @param key The key with value of interest
 * @return The value of the key
*/
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
			value += ft_strlen(key) + 1;
			value = ft_strdup(value);
			break ;
		}
		i++;
	}
	return (value);
}

/**
 * Function creates a duplicate from the environment variable parsed from main,
 * to prevent directly modifying the keys and values of the parent shell.
 * 
 * @param envp the environment variable of the parent shell
 * @return Returns a copy of environment variable
*/
char	**dup_envp(char **envp)
{
	int		i;
	char	**new_envp;

	i = 0;
	while (envp[i] != NULL)
		i++;
	new_envp = (char **)ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (envp[i] != NULL)
	{
		new_envp[i] = ft_strdup(envp[i]);
		i++;
	}
	return(new_envp);
}
