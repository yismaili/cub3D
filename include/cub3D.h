/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:56:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/21 19:04:06 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../libft/libft.h"

typedef struct s_struct
{
	char	**map;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_struct;

int     get_height(char *map_file);
int     get_width(char *map_file);
char    *ft_remplir_map(char *map, char *line);
char	*get_next_line(int fd);
void	ft_read_maps(char *map_file, t_struct *ptr);

#endif