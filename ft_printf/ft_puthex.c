/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:21:26 by zwong             #+#    #+#             */
/*   Updated: 2022/08/16 13:26:58 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	ft_puthex(unsigned int num, int *char_count, char flag)
{
	if (num >= 16)
	{
		ft_puthex(num / 16, char_count, flag);
		num = num % 16;
	}
	if (num < 16)
	{
		if (num <= 9)
			*char_count += ft_putchar(("0123456789")[num]);
		else
		{
			if (flag == 'x')
				*char_count += ft_putchar(("abcdef")[num - 10]);
			if (flag == 'X')
				*char_count += ft_putchar(("ABCDEF")[num - 10]);
		}
	}
}
