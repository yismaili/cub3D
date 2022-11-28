/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_maptool.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 17:13:47 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/28 17:15:02 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	check_elmntof_map(t_struct *cub)
{
	int	i;
	int	j;

	i = 0;
	while (cub->my_map[i])
	{
		j = 0;
		while (cub->my_map[i][j])
		{
			if (cub->my_map[i][j] != 'N' && cub->my_map[i][j] != 'S' && \
					cub->my_map[i][j] != 'W' && cub->my_map[i][j] != 'E' && \
					cub->my_map[i][j] != '1' && cub->my_map[i][j] != '0' && \
					cub->my_map[i][j] != '2' && cub->my_map[i][j] != '\0' && \
					cub->my_map[i][j] != '\n' && cub->my_map[i][j] != ' ')
				return (ft_putstr_fd("Map error\n", 2), 0);
			j++;
		}
		i++;
	}
	return (1);
}

int	ft_check_openmap(char **data)
{
	int	i;
	int	j;

	i = 0;
	while (data[i])
	{
		j = 0;
		while (data[i][j])
		{
			if (data[i][j] == ' ')
				if (data[i][j + 1] != '1' && data[i][j + 1] != ' ' \
						&& data[i][j + 1] != '\0')
					return (1);
			if (data[i][j] == '0')
				if (data[i][j + 1] == ' ' || data[i][j + 1] == '\0' || \
						data[i - 1][j] == ' ' || data[i + 1][j] == ' ' )
					return (1);
			j++;
		}
		i++;
	}
	return (0);
}
