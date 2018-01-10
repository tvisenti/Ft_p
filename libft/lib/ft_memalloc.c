/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 11:48:29 by tvisenti          #+#    #+#             */
/*   Updated: 2015/12/10 12:09:36 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../inc/libft.h"

void		*ft_memalloc(size_t size)
{
	void	*t;

	t = malloc(sizeof(void *) * size);
	if (!t)
		return (NULL);
	ft_memset(t, 0, size);
	return (t);
}
