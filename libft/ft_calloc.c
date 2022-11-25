/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:24:39 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/25 15:25:15 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*dst;
	size_t	i;

	i = 0;
	dst = (char *)malloc(count * size);
	if (!dst)
	{
		ft_putstr_fd("No space lift 'are you kidding me' \n", 2);
		exit(30);
	}
	while (i < count * size)
	{
		dst[i] = 0;
		i++;
	}
	return (dst);
}
