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

char	*expand_env_dollar(t_vars *vars, char *str)
{
	int		i;
	int		j;
	char	*new_str;
	char	*expanded;

	new_str = ft_calloc(1, 1);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			j = ++i;
			while (ft_isalnum(str[j]))
				j++;
			expanded = get_envp_value(vars->envp, ft_substr(str, i, j - i));
			if (expanded)
				new_str = ft_strjoin(new_str, expanded);
		}
		i++;
	}
	free(str);
	return (new_str);
}