#include "../../minishell.h"

int	check_flag(char **argv)
{
	int	i;
	int	j;
	int	flag_count;

	i = 0;
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
		i++;
	}
	return (flag_count);
}

int	func_echo(t_vars *vars, char **argv)
{
	int	i;
	int	flag_count;

	if (argv[1] == 0)
	{
		ft_printf("\n");
		return (0);
	}
	flag_count = check_flag(argv);
	i = flag_count;
	while (argv[i])
	{
		ft_printf(argv[i]);
		if (argv[i + 1] != NULL)
			ft_printf(" ");
		i++;
	}
}