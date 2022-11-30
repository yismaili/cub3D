/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:09:14 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/30 22:03:26 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*ft_check_texture(t_struct *cub, char *dirct, int len)
{
	char	*path;
	int		fd;
	char	*ptr;
	char	*srch;
	char	**new_map;

	new_map = ft_split_map(cub);
	srch = ft_search_innewmap(new_map, dirct, len);
	path = ft_strdup(srch);
	if (!path)
		return (NULL);
	else
	{
		if (typeof_file(path, ".xpm", 4) == -2)
			return (NULL);
		ptr = path;
		path = ft_substr(path, len + 1, (ft_strlen(path) - (len + 1)));
		free(ptr);
		fd = open(path, O_RDONLY);
		if (fd < 0)
			return (NULL);
	}
	free_map(new_map);
	return (path);
}

int	ft_check_alltextures(t_struct *cub)
{
	if (ft_check_alldouble(cub) == 0)
		return (ft_putstr_fd("invalide map\n", 2), 0);
	cub->drct.north_path = ft_check_texture(cub, "NO", 1);
	if (cub->drct.north_path == NULL)
		return (ft_putstr_fd("North texureh not fount\n", 2), 0);
	cub->drct.south_path = ft_check_texture(cub, "SO", 1);
	if (cub->drct.south_path == NULL)
		return (ft_putstr_fd("South texure not fount\n", 2), 0);
	cub->drct.west_path = ft_check_texture(cub, "WE", 1);
	if (cub->drct.west_path == NULL)
		return (ft_putstr_fd("West texure not fount\n", 2), 0);
	cub->drct.east_path = ft_check_texture(cub, "EA", 1);
	if (cub->drct.east_path == NULL)
		return (ft_putstr_fd("East texure not fount\n", 1), 0);
	return (1);
}

int	typeof_file(char *path, char *type, int len)
{
	int	i;
	int	check;

	i = 0;
	check = 0;
	while (path[i])
	{
		if (path[i] == '.')
		{
			check++;
			if (check == 2)
				break ;
		}
		i++;
	}
	if (ft_strncmp(path + i, type, len))
		return (-2);
	return (0);
}

int	ft_check_double(t_struct *cub, char *dirct, int len)
{
	int	cunt;
	int	i;

	i = 0;
	cunt = 0;
	while (cub->map[i])
	{
		if (!ft_strncmp(cub->map[i], dirct, len))
			cunt++;
		i++;
	}
	return (cunt);
}

int	ft_check_alldouble(t_struct *cub)
{
	if (ft_check_double(cub, "NO", 2) != 1 || \
			ft_check_double(cub, "SO", 2) != 1)
		return (0);
	if (ft_check_double(cub, "WE", 2) != 1 || \
			ft_check_double(cub, "EA", 2) != 1)
		return (0);
	if (ft_check_double(cub, "F", 1) != 1 || \
			ft_check_double(cub, "C", 1) != 1)
		return (0);
	return (1);
}
