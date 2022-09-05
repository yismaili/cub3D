/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:53:11 by yismaili          #+#    #+#             */
/*   Updated: 2022/09/05 18:25:40 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char *get_next_line(int fd)
{
    int 	i = 0;
    int 	rd = 0;
    char	character;
    char 	*buffer = malloc(10000);

    while ((rd = read(fd, &character, 1)) > 0)
    {
        if (character == '\n')
            break;
        buffer[i++] = character;
    }
    if ((!buffer[i - 1] && !rd) || rd == -1)
    {
        free(buffer);
        return (NULL);
    }
    buffer[i] =  '\0';
    return(buffer);
}

int	get_height(char *map_file)
{
	int		fd;
	int		height;
	char	*get_line;

	fd = open(map_file, O_RDONLY);
	height = 0;
	get_line = get_next_line(fd);
	while (get_line)
	{
		get_line = get_next_line(fd);
		height ++;
	}
	free(get_line);
	close(fd);
	return (height);
}

int	get_width(char *map_file, int height)
{
	int		fd;
	int		width;
	char	*get_line;
	int i = 0;
	size_t max;

	width = 0;
	max = 0;
	fd = open (map_file, O_RDONLY);
	while (i < height)
	{
		get_line = get_next_line(fd);
		if (ft_strlen(get_line) > max)
			max = ft_strlen(get_line);
		free(get_line);
		i++;
	}
	close(fd);
	return (max);
}

void	ft_read_maps(char *map_file, t_struct *cub)
{
	int		fd;
	int		i;
	char	*get_line;

	i = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
    {
		ft_putstr_fd("Error Open file\n", 1);
        exit(1);
    }
    cub->height = get_height(map_file);
	cub->width = get_width(map_file, cub->height);
	cub->map = (char **) malloc(sizeof(char *) * (cub->height + 1));
	while (i < cub->height)
	{
		// cub->map[i] = (char *) malloc(sizeof(char) * cub->width);
		get_line = get_next_line(fd);
        cub->map[i] = ft_strdup(get_line);
		free(get_line);
		i++;
	}
  	cub->map[i] = NULL;
	close(fd);
}
