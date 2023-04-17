#include "../../minishell.h"

static int	count_words(char const *s)
{
	int		words;
	int		i;
	char	quote_t;

	quote_t = 0;
	words = 0;
	i = 0;
	printf("GIven string: %s\n", s);
	while (s[i] != '\0')
	{
		while (s[i] == ' ')
			i++;
		if (!quote_t && (s[i] == '"' || s[i] == '\''))
			quote_t = s[i++];
		else if (quote_t && s[i] == quote_t)
		{
			quote_t = 0;
			continue ;
		}
		if (!s[i])
			continue;
		if (quote_t)
		{
			while (s[i] != quote_t && s[i] != '\0')
				i++;
			if (s[i + 1] == ' ' || s[i + 1] == '\0')
				words++;
			continue ;
		}
		words++;
		while (s[i] != ' ' && s[i] != '\0')
			i++;
	}
	printf("Words: %d\n", words);
	return (words);
}

static char	*exclude_quotes(char *str)
{
	char	*new;
	char	quote_t;
	int		i;
	int		j;

	if (!(ft_strchr(str, '"') || ft_strchr(str, '\'')))
		return (str);
	new = (char *)ft_calloc(ft_strlen(str), 1);
	i = -1;
	j = 0;
	quote_t = 0;
	while (str[++i])
	{
		if (!quote_t && (str[i] == '"' || str[i] == '\''))
			quote_t = str[i];
		else if (quote_t && str[i] == quote_t)
		{
			quote_t = 0;
			continue ;
		}
		if (str[i] != quote_t) // don't copy if it's quote
			new[j++] = str[i];
	}
	new[j] = 0;
	free(str);
	return (new);
}

char	**parse_split_args(char *s)
{
	char	**splitstr;
	char	quote_t;
	int		start;
	int		end;
	int		i;

	splitstr = (char **)malloc(sizeof(char *) * (count_words(s) + 1));
	if (!s || !splitstr)
		return (0);
	quote_t = 0;
	start = 0;
	end = 0;
	i = -1;
	while (++i < count_words(s))
	{
		while (s[start] == ' ')
			start++;
		if (!quote_t && (s[start] == '"' || s[start] == '\'')) // setter for quote_t
			quote_t = s[start];
		else if (quote_t && s[start] == quote_t)
			quote_t = 0;
		end = start;
		while(quote_t && (end != quote_t && s[end])) // pass through quotes
			end++;
		while (s[end] != ' ' && s[end]) // always stop at spaces
			end++;
		splitstr[i] = exclude_quotes(ft_substr(s, start, end - start));
		start = end;
	}
	splitstr[i] = 0;
	return (splitstr);
}
