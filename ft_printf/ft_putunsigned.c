/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:21:36 by zwong             #+#    #+#             */
/*   Updated: 2022/08/16 13:30:18 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

void	ft_putunsigned(unsigned int num, int *char_count)
{
	if (num >= 10)
	{
		ft_putunsigned(num / 10, char_count);
		num = num % 10;
	}
	if (num < 10)
		*char_count += ft_putchar(num + 48);
}
