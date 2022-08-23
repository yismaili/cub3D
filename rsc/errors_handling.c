/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili <yismaili@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/23 14:39:41 by yismaili         ###   ########.fr       */
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
    if (ft_check_alldouble(cub) == 0)
        return (ft_putstr_fd("invalide map\n", 2), 0);
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

char    **ft_check_florclg(t_struct *cub, char *flor_clg, int len)
{
    char    *data;
    char    *ptr;
    char    **splt_data;
    int     i;
    int     num;

    data = ft_search_inmap(cub, flor_clg, len);
    if (!data)
        return (NULL);
    ptr = data;
    data = ft_substr(data, len + 1, (ft_strlen(data) -(len + 2)));
    free(ptr);
    splt_data = ft_split(data, ',');
    i = 0;
    while (splt_data[i])
    {
        num = ft_atoi(splt_data[i]);
        if (num == -45 || (num < 0 || num > 255))
           return (NULL);
       i++ ;
    }
    if (i < 3 || i > 3)
        return (NULL);
    return (splt_data);
}

int ft_check_rgb(t_struct *cub)
{
    char    **splt_dataflr;
    char    **splt_dataclg;

    if (ft_check_alldouble(cub) == 0)
         return (0);
    splt_dataflr = ft_check_florclg(cub, "F", 1);
    if (splt_dataflr != NULL)
    {
        cub->flr.r = ft_atoi(splt_dataflr[0]);
        cub->flr.g = ft_atoi(splt_dataflr[1]);
        cub->flr.b = ft_atoi(splt_dataflr[2]);
    }
    else
        return (ft_putstr_fd("invalide color\n", 2), 0);
    splt_dataclg = ft_check_florclg(cub, "C", 1);
    if (splt_dataclg != NULL)
    {
        cub->clg.r = ft_atoi(splt_dataclg[0]);
        cub->clg.g = ft_atoi(splt_dataclg[1]);
        cub->clg.b = ft_atoi(splt_dataclg[2]);
    }
    else
        return (ft_putstr_fd("invalide color\n", 2), 0);
    return (1);
}

int ft_check_double(t_struct *cub, char *dirct, int len)
{
    int cunt;
    int i;

    i = 0;
    cunt = 0;
    while (cub->map[i])
    {
        if (!ft_strncmp(cub->map[i], dirct, len))
            cunt++;
        i++;
    }
    return (cunt);
}

int ft_check_alldouble(t_struct *cub)
{
    if (ft_check_double(cub, "NO", 2) == 2 || ft_check_double(cub, "SO", 2) == 2)
        return (0);
    if (ft_check_double(cub, "WE", 2) == 2 || ft_check_double(cub, "EA", 2) == 2)
        return (0);
    if (ft_check_double(cub, "F", 1) == 2 || ft_check_double(cub, "C", 1) == 2)
        return (0);  
    return (1);
}
