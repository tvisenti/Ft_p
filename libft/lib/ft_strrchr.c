/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:40:18 by tvisenti          #+#    #+#             */
/*   Updated: 2015/12/01 17:38:27 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*sav;

	sav = NULL;
	while (*s != '\0')
	{
		if (*s == (char)c)
			sav = (char *)s;
		s++;
	}
	if (*s == (char)c)
		sav = (char *)s;
	return (sav);
}
