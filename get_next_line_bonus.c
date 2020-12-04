/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwyu <hwyu@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/25 21:21:35 by hwyu              #+#    #+#             */
/*   Updated: 2020/07/14 17:56:02 by hwyu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_strlen(const char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		i++;
	}
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*a;
	size_t			i;
	unsigned int	s_length;

	s_length = ft_strlen(s);
	if (s_length < start)
	{
		a = (char *)malloc(sizeof(char) * (1));
		a[0] = '\0';
		return (a);
	}
	i = 0;
	a = (char *)malloc(sizeof(char) * (len + 1));
	if (!a)
		return (NULL);
	while (i < len)
	{
		a[i] = s[start];
		i++;
		start++;
	}
	a[i] = '\0';
	return (a);
}

int		get_next_line3(int fd, char **a, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while (a[fd][i] != '\n' && a[fd][i])
		i++;
	*line = ft_substr(a[fd], 0, i);
	if (a[fd][i] == '\n')
	{
		tmp = ft_strdup(a[fd] + i + 1);
		free(a[fd]);
		a[fd] = tmp;
		if (a[fd][0] == 0)
		{
			free(a[fd]);
			a[fd] = 0;
		}
		return (1);
	}
	free(a[fd]);
	a[fd] = 0;
	return (0);
}

int		get_next_line2(int fd, char **a, int ret, int i)
{
	char	buf[BUFFER_SIZE + 1];
	char	*tmp;

	ret = 0;
	if (a[fd][i] != '\n')
	{
		while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
		{
			buf[ret] = '\0';
			tmp = ft_strjoin(a[fd], buf);
			free(a[fd]);
			a[fd] = tmp;
			while (a[fd][i] != '\n' && a[fd][i])
				i++;
			if (a[fd][i] == '\n')
				break ;
		}
		if (ret < 0)
		{
			free(a[fd]);
			a[fd] = 0;
			return (-1);
		}
	}
	return (ret);
}

int		get_next_line(int fd, char **line)
{
	static char	*a[255];
	int			ret;
	int			i;

	ret = 0;
	if (line == NULL)
		return (-1);
	if (fd < 0)
		return (-1);
	if (BUFFER_SIZE <= 0)
		return (-1);
	i = 0;
	if (a[fd] == NULL)
		a[fd] = ft_strnew(1);
	while (a[fd][i] != '\n' && a[fd][i])
		i++;
	ret = get_next_line2(fd, a, ret, i);
	if (ret < 0)
		return (ret);
	if (ret == 0 && a[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	return (get_next_line3(fd, a, line));
}
