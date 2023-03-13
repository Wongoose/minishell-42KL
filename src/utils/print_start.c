/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 13:44:52 by chenlee           #+#    #+#             */
/*   Updated: 2023/03/13 14:20:18 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define C_RED "\e[0;31m"
#define C_YEL "\e[0;33m"
#define C_BLU "\e[0;34m"
#define C_CYN "\e[0;36m"
#define C_RST "\e[m"

char	**init_text(void)
{
	char	**text;

	text = malloc(sizeof(char *) * 13);
	text[0] = ft_strdup("___  ________ _   _ _____ _____");
	text[1] = ft_strdup(" _   _  _____ _      _");
	text[2] = ft_strdup("|  \\/  |_   _| \\ | |_   _/  ___");
	text[3] = ft_strdup("| | | ||  ___| |    | |");
	text[4] = ft_strdup("| .  . | | | |  \\| | | | \\ `--.");
	text[5] = ft_strdup("| |_| || |__ | |    | |");
	text[6] = ft_strdup("| |\\/| | | | | . ` | | |  `--. \\");
	text[7] = ft_strdup("  _  ||  __|| |    | |");
	text[8] = ft_strdup("| |  | |_| |_| |\\  |_| |_/\\__/ /");
	text[9] = ft_strdup(" | | || |___| |____| |____");
	text[10] = ft_strdup("\\_|  |_/\\___/\\_| \\_/\\___/\\____/");
	text[11] = ft_strdup("\\_| |_/\\____/\\_____/\\_____/");
	text[12] = NULL;
	return (text);
}

void	print_startup(void)
{
	int		i;
	char	**hell;

	hell = init_text();
	i = 0;
	while (i < 11)
	{
		ft_printf(C_YEL "     %s", hell[i]);
		ft_printf(C_RED "%s\n", hell[i + 1]);
		i += 2;
	}
	ft_printf(C_RST "\n");
	free_doublearray(hell);
	ft_printf("           By: chenlee(sirhcofe) && zwong(Wongoose)\n\n");
}

// ___  ________ _   _ _____ _____ _   _  _____ _      _     
// |  \/  |_   _| \ | |_   _/  ___| | | ||  ___| |    | |    
// | .  . | | | |  \| | | | \ `--.| |_| || |__ | |    | |    
// | |\/| | | | | . ` | | |  `--. \  _  ||  __|| |    | |    
// | |  | |_| |_| |\  |_| |_/\__/ / | | || |___| |____| |____
// \_|  |_/\___/\_| \_/\___/\____/\_| |_/\____/\_____/\_____/