/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:00:11 by yismaili          #+#    #+#             */
/*   Updated: 2022/11/28 17:35:42 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char	*ft_search_innewmap(char **new_map, char *search, int len_ofsrch)
{
	int	i;

	i = 0;
	while (new_map[i])
	{
		if (!ft_strncmp(new_map[i], search, len_ofsrch))
			return (new_map[i]);
		i++;
	}
	return (NULL);
}

char	**ft_check_florclg(t_struct *cub, char *flor_clg, int len)
{
	char	*data;
	char	*ptr;
	char	**splt_data;
	char	*srch;
	char	**new_map;

	new_map = ft_split_map(cub);
	srch = ft_search_innewmap(new_map, flor_clg, len);
	free_map(new_map);
	data = ft_strdup(srch);
	if (!data)
		return (NULL);
	ptr = data;
	data = ft_substr(data, len, (ft_strlen(data) - (len)));
	free(ptr);
	if (handling_rgb(data) != 2)
		return (NULL);
	splt_data = ft_split(data, ',');
	free(data);
	return (convert_tonum(splt_data));
}

char	**convert_tonum(char **splt_data)
{
	int	i;
	int	num;

	i = 0;
	while (splt_data[i])
	{
		if (ft_check_isnum(splt_data[i]))
			return (NULL);
		num = ft_atoi(splt_data[i]);
		if (num == -45 || (num < 0 || num > 255))
			return (NULL);
		i++;
	}
	if (i < 3 || i > 3)
		return (NULL);
	return (splt_data);
}

int	ft_check_rgb(t_struct *cub)
{
	char	**splt_dataflr;
	char	**splt_dataclg;

	if (ft_check_alldouble(cub) == 0)
		return (0);
	splt_dataflr = ft_check_florclg(cub, "F", 1);
	if (splt_dataflr != NULL)
	{
		remplir_rgb_flor(cub, splt_dataflr);
		free_map(splt_dataflr);
	}
	else
		return (ft_putstr_fd("invalide color\n", 2), 0);
	splt_dataclg = ft_check_florclg(cub, "C", 1);
	if (splt_dataclg != NULL)
	{
		cub->clg.r = ft_atoi(splt_dataclg[0]);
		cub->clg.g = ft_atoi(splt_dataclg[1]);
		cub->clg.b = ft_atoi(splt_dataclg[2]);
		free_map(splt_dataclg);
	}
	else
		return (ft_putstr_fd("invalide color\n", 2), 0);
	return (1);
}

void	remplir_rgb_flor(t_struct *cub, char **splt_dataflr)
{
	cub->flr.r = ft_atoi(splt_dataflr[0]);
	cub->flr.g = ft_atoi(splt_dataflr[1]);
	cub->flr.b = ft_atoi(splt_dataflr[2]);
}
