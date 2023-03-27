#include "../../minishell.h"

int	count_flags(char **argv)
{
	int	i;
	int	j;
	int	flag_count;

	i = 1;
	flag_count = 0;
	while (argv[i])
	{
		j = 0;
		if (argv[i][j] == '-' && argv[i][++j] == 'n')
		{
			while (argv[i][j] == 'n')
			{
				if (argv[i][j] == '\0')
					break ;
				j++;
			}
			if (argv[i][j] == '\0')
				flag_count++;
		}
		else
			break ;
		i++;
	}
	return (flag_count);
}

int	func_echo(t_vars *vars, char **argv)
{
	int		i;
	int		flag_count;
	(void)	vars;

	if (argv[1] == 0)
	{
		ft_printf("\n");
		return (0);
	}
	flag_count = count_flags(argv);
	i = flag_count + 1; // before printing, jump pass the number of -n
	while (argv[i])
	{
		ft_printf(argv[i]);
		if (argv[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
	if (flag_count == 0)
		ft_printf("\n");
	return (0);
}
