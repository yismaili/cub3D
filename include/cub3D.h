/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:56:15 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/21 16:25:54 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"

typedef struct s_struct
{
	int		width;
	int		height;
	char		**map;
	void	*mlx_ptr;
	void	*win_ptr;
}	t_struct;

int     get_height(char *map_file);
int     get_width(char *map_file);
void	ft_rempier_map(int *map, char *line);
void	ft_read_maps(char *map_file, t_struct *ptr);

#endif