/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 09:28:30 by tvisenti          #+#    #+#             */
/*   Updated: 2015/12/10 09:31:56 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*str;

	str = (unsigned char*)malloc(sizeof(*str) * len);
	ft_memcpy(str, src, len);
	ft_memcpy(dst, str, len);
	free(str);
	return (dst);
}
