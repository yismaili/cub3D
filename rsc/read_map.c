/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:53:11 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/23 19:40:43 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char *get_next_line(int fd)
{
	char line[8000000] = {0};
	int ret = 1;
	char c;
	int i = 0;
	while((ret = read(fd, &c, 1) > 0))
	{
		line[i++] = c;
		if (c == '\n')
			break ;
	}
	if (line[0] == 0)
		return NULL;
	return (ft_strdup(line));
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

int	get_width(char *map_file)
{
	int		fd;
	char	**words;
	int		width;
	char	*get_line;
	int		i;

	width = 0;
	fd = open (map_file, O_RDONLY);
	get_line = get_next_line(fd);
	words = ft_split(get_line, ' ');
	while (words[width])
	{
		width++;
	}
	close(fd);
	free(get_line);
	i = 0;
	while (words[i])
		free(words[i++]);
	free(words);
	return (width);
}

char    *ft_remplir_map(char *map, char *line)
{
	char	**spltd;
	int		i;

	i = 0;
    map = NULL;
	spltd = ft_split(line, ' ');
	while (spltd[i])
	{
		map = ft_strjoin(map, spltd[i]);
        i++;
	}
	i = 0;
	while (spltd[i])
		free(spltd[i++]);
	free(spltd);
    return (map);
}

void	ft_read_maps(char *map_file, t_struct *cub)
{
	int		fd;
	int		i;
	char	*get_line;
    int     height;

	i = 0;
	fd = open(map_file, O_RDONLY);
	if (fd < 0)
    {
		ft_putstr_fd("Error Open file\n", 1);
        exit(1);
    }
    height = get_height(map_file);
	cub->map = (char **) malloc(sizeof(char *) * (height + 1));
	while (i < height)
	{
		cub->map[i] = (char *) malloc(sizeof(char) * get_width(map_file));
		get_line = get_next_line(fd);
        // cub->map[i] = ft_remplir_map(cub->map[i], get_line);
        cub->map[i] = ft_strdup(get_line);
		free(get_line);
		i++;
	}
  	cub->map[i] = NULL;
	close(fd);
}
