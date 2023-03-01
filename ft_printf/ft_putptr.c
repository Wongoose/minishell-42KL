/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:21:31 by zwong             #+#    #+#             */
/*   Updated: 2022/08/16 13:44:01 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

static void	puthex(uintptr_t num, int *char_count)
{
	if (num >= 16)
	{
		puthex(num / 16, char_count);
		num = num % 16;
	}
	if (num < 16)
		*char_count += ft_putchar(("0123456789abcdef")[num]);
}

void	ft_putptr(uintptr_t num, int *char_count)
{
	ft_putstr("0x", char_count);
	puthex(num, char_count);
}

// if (!num)
// 	return (ft_putstr("(nil)", char_count));
