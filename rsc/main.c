/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/28 18:38:01 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_close(int keycode)
{
	if (keycode)
		exit(1);
	return (0);
}

void	hooking(t_struct *cub)
{
	mlx_hook(cub->win_ptr, 02, 0, KeyPress ,cub);
	mlx_hook(cub->win_ptr, 03, 0, KeyRelease, cub);
	mlx_loop_hook(cub->mlx_ptr, player_move, cub);
	mlx_hook(cub->win_ptr, 06, (1L<<8), MotionNotify, cub);
	mlx_hook(cub->win_ptr, 17, 0, ft_close, cub);
	mlx_loop(cub->mlx_ptr);
}

int	MotionNotify(int x, int y, t_struct *cub)
{ 
	if (x > 0 && x < W_WIDTH && y > 0 && y < W_HEIGHT)
	{
		if(cub->med_x < x)
			cub->player.rottAngle += cub->player.rottSpeed/6;
		if(cub->med_x > x)
			cub->player.rottAngle -= cub->player.rottSpeed/6;
		if(cub->med_x == x)
			cub->player.rottAngle =  cub->player.rottAngle;
		cub->med_x = x;
	}
	return (0);
}

int	typeofmap(char *path, char *type, int len)
{
	int	i;

	i = 0;
	while (path[i])
	{
		if(path[i] == '.')
		{
			break;
		}
		i++;
	}
	if	(ft_strncmp(path + i, type, len))
		return (-2);
	return (0);
}

int	main(int ac, char **av)
{
	t_struct 	cub;
	int 		i;

	cub.scaleHeight = 64;
	cub.scaleWidth = 64;
	cub.texture_height = 64;
	cub.texture_width = 64;
	cub.med_x = W_WIDTH / 2;
	if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3D path/to/map.cub", 0), 0);
	if (typeofmap(av[1], ".cub", 4) == -2)
		return (ft_putstr_fd("type of map incorrect\n", 0), 0);
	if (ft_read_maps(av[1], &cub) == 0)
		return (0);
	ft_jump_lines(&cub);
	if (!ft_check_alltextures(&cub))
		return (0);
	if (!ft_check_rgb(&cub))
		return (0);
	if (!ft_check_map(&cub))
		return (0);
	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, W_WIDTH, W_HEIGHT, "cub3D");
	cub.color_buffer = (unsigned int **) ft_calloc(sizeof(unsigned int *), W_HEIGHT);
	i = -1;
	while (++i < W_HEIGHT)
		cub.color_buffer[i] = (unsigned int *)ft_calloc(sizeof(unsigned int), W_WIDTH);
	ft_colorBuffer(&cub);
	cub.wallTexture = (unsigned int *) ft_calloc (sizeof(unsigned int), (unsigned int)cub.scaleWidth * (unsigned int)cub.scaleHeight);
	for(int x=0; x < cub.scaleWidth; x++)
	{
		for(int y = 0; y < cub.scaleHeight;y++)
        {
            //put the value black or blue based on x and y being a multiple
            if(x % 8  && y % 8 )
            {
                cub.wallTexture[(cub.scaleWidth * y) + x] = 0xadd8e6;
            }
            else{
                cub.wallTexture[(cub.scaleWidth * y) + x] = 0xFFF0000;
            }
        }
    }
    cub.img = mlx_new_image(cub.mlx_ptr, W_WIDTH, W_HEIGHT);
	cub.addr = (int *)mlx_get_data_addr(cub.img, &cub.bits_per_pixel, &cub.line_length, &cub.endian);
    player_position(&cub);
    directionOfPlayer(&cub);
    cub.widthofmap = cub.scaleWidth * cub.widthof_minimap;
    cub.heightofmap = cub.scaleHeight * cub.heightof_minimap;
    loading_map(&cub);
    ft_draw_map(&cub);
    hooking(&cub);
    while (1)
    {
        /* code */
    }
    
    return (0);
}

void	loading_map(t_struct *cub)
{
    cub->img2 = mlx_xpm_file_to_image(cub->mlx_ptr, cub->drct.north_path,&cub->texture_width, &cub->texture_height);
	if (!cub->img2)
		return ;
	cub->data = (int *)mlx_get_data_addr(cub->img2, &cub->bits_per_pixel2, &cub->size_line, &cub->endian2);
	if (!cub->data || cub->texture_width != cub->texture_height)
		return ;
}
