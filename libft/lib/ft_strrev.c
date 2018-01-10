/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 14:39:22 by tvisenti          #+#    #+#             */
/*   Updated: 2015/12/03 15:26:46 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/libft.h"

char		*ft_strrev(char *str)
{
	int		i;
	int		k;
	char	c;

	i = 0;
	k = ft_strlen(str) - 1;
	while (i < k)
	{
		c = str[i];
		str[i] = str[k];
		str[k] = c;
		i++;
		k--;
	}
	return (str);
}
