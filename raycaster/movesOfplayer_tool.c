/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movesOfplayer_tool.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:19:05 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 23:04:19 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	ft_close(int keycode)
{
	if (keycode)
		exit(1);
	return (0);
}

int	motion_notify(int x, int y, t_struct *cub)
{
	if (x > 0 && x < W_WIDTH && y > 0 && y < W_HEIGHT)
	{
		if (cub->med_x < x)
			cub->player.rottangle += cub->player.rottspeed / 6;
		if (cub->med_x > x)
			cub->player.rottangle -= cub->player.rottspeed / 6;
		if (cub->med_x == x)
			cub->player.rottangle = cub->player.rottangle;
		cub->med_x = x;
	}
	return (0);
}
