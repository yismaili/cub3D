/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/30 14:58:52 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	hooking(t_struct *cub)
{
	mlx_hook(cub->win_ptr, 02, 0, key_press, cub);
	mlx_hook(cub->win_ptr, 03, 0, key_release, cub);
	mlx_hook(cub->win_ptr, 17, 0, ft_close, cub);
	mlx_loop_hook (cub->mlx_ptr, player_move, cub);
	mlx_hook(cub->win_ptr, 06, (1L << 8), motion_notify, cub);
	mlx_loop(cub->mlx_ptr);
}

int	check_input(t_struct *cub, char **av, int ac)
{
	cub->scaleheight = 64;
	cub->scalewidth = 64;
	cub->texture_height = 64;
	cub->texture_width = 64;
	cub->player.rottspeed = 0.114533;
	cub->player.walkdrctn = 0;
	cub->numofrays = W_WIDTH;
	cub->med_x = W_WIDTH / 2;
	cub->angleincrem = (M_PI / 3) / cub->numofrays;
	if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3D path/to/map.cub", 0), 0);
	if (typeofmap(av[1], ".cub", 4) == -2)
		return (ft_putstr_fd("type of map incorrect\n", 0), 0);
	if (ft_read_maps(av[1], cub) == 0)
		return (0);
	ft_jump_lines(cub);
	if (!ft_check_alltextures(cub))
		return (0);
	if (!ft_check_rgb(cub))
		return (0);
	if (!ft_check_map(cub))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_struct	cub;

	if (check_input(&cub, av, ac) == 0)
		return (0);
	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, W_WIDTH, W_HEIGHT, "cub3D");
	cub.color_buffer = (unsigned int **) ft_calloc(sizeof(unsigned int *), \
			W_HEIGHT);
	cub.img = mlx_new_image(cub.mlx_ptr, W_WIDTH, W_HEIGHT);
	cub.addr = (int *)mlx_get_data_addr(cub.img, &cub.bits_per_pixel, \
			&cub.line_length, &cub.endian);
	color_oftexture(&cub);
	player_position(&cub);
	direction_of_player(&cub);
	cub.widthofmap = cub.scalewidth * cub.widthof_minimap;
	cub.heightofmap = cub.scaleheight * cub.heightof_minimap;
	init_textures(&cub);
	ft_draw_map(&cub);
	hooking(&cub);
	return (0);
}
