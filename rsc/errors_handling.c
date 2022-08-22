/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/22 22:07:07 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char    *ft_search_inmap(t_struct *cub, char *search, int len_ofsrch)
{
    int i;

    i = 0;
    while (cub->map[i])
    {
        if (!ft_strncmp(cub->map[i], search, len_ofsrch))
            return (cub->map[i]);
        i++;
    }
    return (NULL);
}

int ft_check_texture(t_struct *cub, char *dirct, int len)
{
    char    *path;
    int     fd;
    char    *ptr;

    path = ft_search_inmap(cub, dirct, len);
    if (!path)
        return (0);
    else
    {
        ptr = path;
        path = ft_substr(path, len + 1, (ft_strlen(path) - (len + 2)));
        free(ptr);
         fd = open(path, O_RDONLY);
         if (fd < 0)
            return (0);
        else //for testing
            printf("GOOD\n");
    }
    return (1);
}

int ft_check_alltextures(t_struct *cub)
{
    if (ft_check_texture(cub, "NO", 2) == 0)
        return (ft_putstr_fd("North texureh not fount\n", 2), 0);
    if (ft_check_texture(cub, "SO", 2) == 0)
        return (ft_putstr_fd("South texure not fount\n", 2), 0);
    if (ft_check_texture(cub, "WE", 2) == 0)
        return (ft_putstr_fd("West texure not fount\n", 2), 0);
    if (ft_check_texture(cub, "EA", 2) == 0)
        return (ft_putstr_fd("East texure not fount\n", 2), 0);
    return (1);
}