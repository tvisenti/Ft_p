/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvisenti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:04:41 by tvisenti          #+#    #+#             */
/*   Updated: 2015/12/06 13:36:58 by tvisenti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_putnbr(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if ((unsigned int)n > 9)
	{
		ft_putnbr((unsigned int)n / 10);
		ft_putnbr((unsigned int)n % 10);
	}
	else
		ft_putchar((unsigned int)n + '0');
}
