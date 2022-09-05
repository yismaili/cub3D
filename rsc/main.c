/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 16:46:01 by yismaili          #+#    #+#             */
/*   Updated: 2022/09/05 18:26:34 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void print(char **str)
{
     int i = 0;
    while (str[i])
    {
        printf("|%s|\n",str[i]);
        i++;
    }
}

int main(int ac, char **av)
{
    t_struct cub;

    if (ac != 2)
		return (ft_putstr_fd("Usage : ./cub3D path/to/map.cub", 0), 0);
	ft_read_maps(av[1], &cub);
    ft_check_alltextures(&cub);
    ft_check_rgb(&cub);
    ft_check_map(&cub);
    
    int i = 6;
    int j = 0;
    char **map = ft_calloc(sizeof(char *), cub.width + 1);
    while (cub.map[i++] && i < cub.height)
    {
        // printf("%p\n", cub.map[i]);
        map[j] = ft_calloc(sizeof(char), cub.width + 1);
        ft_memset(map[j], ' ', cub.width);
        map[j][cub.width] = '\0';
        ft_memmove(map[j], cub.map[i], ft_strlen(cub.map[i]));
        j++;
    }
    
    // printf("\n%d\n",cub.flr.r);
    // printf("NO --->%s\n",cub.drct.north_path);
    // printf("SO --->%s\n",cub.drct.south_path);
    // printf("WE --->%s\n",cub.drct.west_path);
    // printf("EA --->%s\n",cub.drct.east_path);
    //  print(data);
    //  printf("-------------------------------------------------------\n");
    print(map);
    
}