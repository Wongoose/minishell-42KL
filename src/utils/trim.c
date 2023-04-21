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

static int	update_paren(char c, int paren)
{
	if (c == '(')
	{
		if (paren == -1)
			paren = 0;
		paren++;
	}
	else if (c == ')')
		paren--;
	return (paren);
}

char	*ft_trim_paren(char *str)
{
	int		i;
	int		paren;
	char	*ret;

	if (!str)
		return (NULL);
	paren = -1;
	i = 0;
	ret = ft_strdup(str);
	while (str[i])
	{
		paren = update_paren(str[i], paren);
		if (paren == 0)
		{
			if (i == (int)(ft_strlen(str) - 1))
				ret = ft_trim_paren(ft_substr(str, 1, ft_strlen(str) - 2));
			break ;
		}
		i++;
	}
	return (ret);
}