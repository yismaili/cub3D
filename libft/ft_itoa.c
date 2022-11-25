/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:47:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/25 15:35:58 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_lennum(int num)
{
	int			len;
	long int	n;

	n = num;
	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		len++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int			len;
	char		*dest;
	long int	num;
	int			i;

	num = n;
	len = 0;
	i = 0;
	len = ft_lennum(num);
	dest = (char *)ft_calloc(sizeof(char), (len + 1) );
	if (!dest)
		return (NULL);
	dest[len] = '\0';
	if (num < 0)
	{
		dest[0] = '-';
		num = num * (-1);
	}
	while (len-- > (n < 0))
	{
		dest[len] = num % 10 + 48;
		num /= 10;
	}
	return (dest);
}
