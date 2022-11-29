/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movesOfplayer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:51:53 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/29 15:03:22 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

int	player_move(t_struct *cub)
{ 
	check_nextsteep(cub);
	check_downsteep(cub);
    if (cub->player.angle == 1 || cub->player.angle == -1)
        cub->player.rottAngle += (cub->player.rottSpeed * cub->player.angle);
     cub->player.angle = 0;
    ft_draw_map(cub);
    return (0);
}

int key_press(int key, t_struct *cub)
{
	if (key == 1)
        cub->player.walkDrctn = -1;
	else if (key == 13)
        cub->player.walkDrctn = 1;
	else if (key == 2)
        cub->player.walkDown = 1;
	else if (key == 0)
        cub->player.walkDown= -1;
    else if (key == 124)
        cub->player.angle = 1;
    else if (key == 123)
        cub->player.angle = -1;
    return (0);
}

int	key_release(int key, t_struct *cub)
{ 
    (void)key;
    cub->player.walkDrctn = 0;
    cub->player.walkDrctn = 0;
    cub->player.walkDown = 0;
    cub->player.walkDown= 0;
    cub->player.angle = 0;
    return (0);
}

void check_nextsteep(t_struct *cub)
{
  double  new_x;
  double  new_y;

    new_x = cub->player.position_x + (cos(cub->player.rottAngle) * ((double)cub->player.walkDrctn * 4));
    new_y = cub->player.position_y + (sin(cub->player.rottAngle) * ((double)cub->player.walkDrctn * 4));
    if (check_wall(cub, new_x, new_y) != 1)
    {
        cub->player.position_x = new_x;
        cub->player.position_y = new_y;
    }   
}

void check_downsteep(t_struct *cub)
{
  double  new_x;
  double  new_y;

    new_x = cub->player.position_x + (cos(cub->player.rottAngle + (M_PI/2)) * 4) * cub->player.walkDown;
    new_y = cub->player.position_y + (sin(cub->player.rottAngle + (M_PI/2)) * 4) * cub->player.walkDown;
    if (check_wall(cub, new_x, new_y) != 1)
    {
        cub->player.position_x = new_x;
        cub->player.position_y = new_y;
    }   
}
