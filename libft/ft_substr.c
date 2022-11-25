/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 17:48:09 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/25 15:32:41 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dst;
	size_t			j;
	size_t			i;

	j = 0;
	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	dst = (char *)ft_calloc(sizeof(char), (len + 1));
	if (!dst)
		return (NULL);
	while (s[i])
	{
		if (i >= start && j < len)
		{
			dst[j] = s[i];
			j++;
		}
		i++;
	}
	dst[j] = '\0';
	return (dst);
}
