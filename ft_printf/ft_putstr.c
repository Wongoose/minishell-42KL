/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:21:34 by zwong             #+#    #+#             */
/*   Updated: 2022/08/16 13:29:57 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	ft_putstr(char *str, int *char_count)
{
	if (!str)
		return (ft_putstr("(null)", char_count));
	while (*str)
		*char_count += ft_putchar(*(str++));
}
