/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zwong <zwong@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 13:21:03 by zwong             #+#    #+#             */
/*   Updated: 2022/08/16 13:32:48 by zwong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>

int		ft_printf(const char *str, ...);
int		ft_putchar(int c);
void	ft_putstr(char *str, int *char_count);
void	ft_putnbr(int num, int *char_count, char flag);
void	ft_puthex(unsigned int num, int *char_count, char flag);
void	ft_putptr(uintptr_t num, int *char_count);
void	ft_putunsigned(unsigned int num, int *char_count);

#endif