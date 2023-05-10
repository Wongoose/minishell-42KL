/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_rdr_char.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 17:42:32 by zwong             #+#    #+#             */
/*   Updated: 2023/05/10 17:42:35 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_rdr_char(char value)
{
	return (value == '>' || value == '<');
}

t_bool	is_rdr_str(char *value)
{
	return (ft_strcmp(value, ">") == 0 || ft_strcmp(value, ">>") == 0
		|| ft_strcmp(value, "<") == 0 || ft_strcmp(value, "<<") == 0);
}
