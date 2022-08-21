/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yismaili < yismaili@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 01:29:18 by yismaili          #+#    #+#             */
/*   Updated: 2022/08/21 16:43:09 by yismaili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	1000
# endif

char	*get_next_line(int fd);
char	*ft_read(int fd, char *left_str);
size_t	ft_strlen_g(char *s);
char	*ft_strchr_g(char *s, int c);
char	*ft_strjoin_g(char *left_str, char *buff);
char	*ft_next_str(char *left_str);
char	*ft_get_line(char *left_str);

#endif
