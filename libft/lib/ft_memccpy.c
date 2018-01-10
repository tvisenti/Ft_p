/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 18:17:49 by tvisenti          #+#    #+#             */
/*   Updated: 2015/12/10 09:56:19 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void			*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*pdst;
	unsigned char		*psrc;
	unsigned int		i;

	i = 0;
	pdst = (unsigned char *)dst;
	psrc = (unsigned char *)src;
	while (n--)
	{
		*pdst = *psrc;
		if (*psrc == (unsigned char)c)
			return ((void *)(pdst + 1));
		pdst++;
		psrc++;
	}
	return (NULL);
}
