/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/24 16:21:28 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void print(char **str)
{
     int i = 0;
    while (str[i])
    {
        printf("%s",str[i]);
        i++;
    }
}

int main(int ac, char **av)
{
    t_struct cub;
    char    **data;
    if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3D path/to/map.cub", 0), 0);
	ft_read_maps(av[1], &cub);
    ft_check_alltextures(&cub);
    ft_check_rgb(&cub);
    data = ft_jump_lines(&cub);
    // printf("\n%d\n",cub.flr.r);
    // printf("NO --->%s\n",cub.drct.north_path);
    // printf("SO --->%s\n",cub.drct.south_path);
    // printf("WE --->%s\n",cub.drct.west_path);
    // printf("EA --->%s\n",cub.drct.east_path);
     print(data);
    
}