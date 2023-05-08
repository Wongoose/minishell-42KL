/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 17:47:37 by zwong             #+#    #+#             */
/*   Updated: 2023/05/08 17:48:02 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	update_quote_t(char quote_t, char value)
{
	if (!quote_t && ft_isquote(value))
		return (value);
	else if (quote_t && value == quote_t)
		return (0);
	return (quote_t);
}
