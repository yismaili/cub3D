/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_color_tool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:05:34 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 14:07:32 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	**ft_split_map(t_struct *c)
{
	c->tmp.i = 0;
	c->tmp.check = 0;
	c->tmp.k = 0;
	c->tmp.len = 0;
	c->tmp.path = (char **)ft_calloc(sizeof(char *), c->height + 1);
	while (c->height > c->tmp.i)
	{
		c->tmp.j = 0;
		c->tmp.l = 0;
		c->tmp.path[c->tmp.k] = ft_calloc(sizeof(char), \
				len_ofpath(c->map[c->tmp.i]) + 1);
		while (c->map[c->tmp.i][c->tmp.j])
		{
			if (c->map[c->tmp.i][c->tmp.j] != ' ' && c->tmp.check < 7)
				c->tmp.path[c->tmp.k][c->tmp.l++] = c->map[c->tmp.i][c->tmp.j];
			if (c->map[c->tmp.i][c->tmp.j] == ' ')
				c->tmp.check++;
			c->tmp.j++;
		}
		c->tmp.path[c->tmp.k][c->tmp.l] = '\0';
	printf("%s\n", c->tmp.path[c->tmp.k]);
		c->tmp.k++;
		c->tmp.i++;
	}
	return (c->tmp.path);
}

int	len_ofpath(char *path)
{
	int	j;
	int	len;

	len = 0;
	j = 0;
	while (path[j])
	{
		if (path[j] != ' ')
			len++;
		j++;
	}
	return (len);
}

int	ft_check_isnum(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		if (!ft_isdigit(num[i]))
			return (1);
		i++;
	}
	return (0);
}

int	handling_rgb(char *data)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (data[i])
	{
		if (data[i] == ',')
			len++;
		i++;
	}
	return (len);
}
