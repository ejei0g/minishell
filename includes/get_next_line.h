/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwyu <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 20:20:59 by hwyu              #+#    #+#             */
/*   Updated: 2020/12/22 16:55:37 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _GET_NEXT_LINE_H
# define _GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

char	*ft_strnew(size_t size);
int		get_next_line(int fd, char **line);
int		get_next_line2(int fd, char **a, int ret, int i);
int		get_next_line3(int fd, char **a, char **line);

#endif
