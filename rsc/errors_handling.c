/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/28 17:14:57 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	ft_jump_lines(t_struct *cub)
{
	int	len;

	len = 0;
	while (cub->map[len])
	{
		if (ft_strchr(cub->map[len], 'N') || ft_strchr(cub->map[len], 'S') \
				|| ft_strchr(cub->map[len], 'W') \
				|| ft_strchr(cub->map[len], 'E') \
				|| ft_strchr(cub->map[len], 'F') \
				|| ft_strchr(cub->map[len], 'C') \
				|| cub->map[len][0] == '\0' || \
				cub->map[len][0] == '\n')
			len++;
		else
			break ;
	}
	set_map(cub, len);
	return ;
}

void	set_map(t_struct *cub, int len)
{
	int	i;

	cub->my_map = ft_calloc(sizeof(char *), (cub->height - len) + 1);
	i = 0;
	while (cub->map[len])
	{
		cub->my_map[i] = ft_calloc(sizeof(char), cub->width + 1);
		ft_memset(cub->my_map[i], ' ', cub->width);
		cub->my_map[i][cub->width] = '\0';
		ft_memmove(cub->my_map[i], cub->map[len], ft_strlen(cub->map[len]));
		len++;
		i++;
	}
	cub->len_ofmap = i;
	cub->my_map[i] = NULL;
}

int	ft_check_bgnend(char *data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i] == '0')
			return (0);
		i++;
	}
	return (1);
}

int	count_direction(char **str)
{
	int	i;
	int	len;
	int	j;

	i = 0;
	j = 0;
	len = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (ft_isalpha(str[i][j]))
				len++;
			j++;
		}
		i++;
	}
	return (len);
}

int	ft_check_map(t_struct *cub)
{
	cub->heightof_minimap = ft_count_height(cub);
	cub->widthof_minimap = ft_strlen(cub->my_map[1]);
	if (count_direction(cub->my_map) != 1)
		return (ft_putstr_fd("too many direction", 2), 0);
	if (ft_check_bgnend(cub->my_map[0]) == 0)
		return (ft_putstr_fd("Open map\n", 2), 0);
	if (ft_check_bgnend(cub->my_map[cub->len_ofmap - 1]) == 0)
		return (ft_putstr_fd("Open map\n", 2), 0);
	if (check_elmntof_map(cub) == 0)
		return (0);
	if (ft_check_openmap(cub->my_map))
		return (ft_putstr_fd("Open map\n", 2), 0);
	return (1);
}
