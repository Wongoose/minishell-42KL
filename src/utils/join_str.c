/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chenlee <chenlee@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 19:27:19 by chenlee           #+#    #+#             */
/*   Updated: 2023/05/04 19:27:23 by chenlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_str(char *front, char *middle, char *rear)
{
	char	*temp;
	char	*ret;

	if (middle != NULL)
	{
		temp = ft_strjoin(front, middle);
		if (front != NULL)
			free(front);
		free(middle);
	}
	else
		temp = front;
	ret = ft_strjoin(temp, rear);
	if (temp != NULL)
		free(temp);
	if (rear != NULL)
		free(rear);
	return (ret);
}
