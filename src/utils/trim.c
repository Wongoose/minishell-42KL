#include "minishell.h"

char	*ft_trim(char *str)
{
	int i;
	int	j;

	if (!str)
		return (NULL);
	i = 0;
	j = ft_strlen(str) - 1;
	while (str[i] == ' ' && str[i])
		i++;
	while (str[j] == ' ' && j != 0)
		j--;
	return (ft_substr(str, i, j - i + 1));		
}

char	*ft_trim_paren(char *str)
{
	int	i;
	int	j;

	if (!str)
		return (NULL);
	i = 0;
	j = ft_strlen(str) - 1;
	return (ft_substr(str, i + 1, j - i - 1));
}