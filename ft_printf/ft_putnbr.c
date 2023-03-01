/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:21:29 by zwong             #+#    #+#             */
/*   Updated: 2022/08/16 13:27:45 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	ft_putnbr(int nb, int *char_count, char flag)
{
	unsigned int	num;

	if (nb < 0)
	{
		*char_count += ft_putchar('-');
		num = (unsigned int)-nb;
	}
	else
		num = nb;
	if (num >= 10)
	{
		ft_putnbr(num / 10, char_count, flag);
		num = num % 10;
	}
	if (num < 10)
		*char_count += ft_putchar(num + 48);
}
