/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: souchen <souchen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 21:24:03 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/22 21:15:17 by yismaili         ###   ########.fr       */
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

    path = ft_search_inmap(cub, dirct, len);
    if (!path)
        return (ft_putstr_fd("File path not fount\n",2),0);
    else
    {
         path = path + len + 3;
         printf("%s\n",path);
         fd = open(path, O_RDONLY);
         if (fd < 0)
            return (ft_putstr_fd("Error Open file\n", 2), 0);
    }
    return (1);
}
