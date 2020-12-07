/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 17:39:05 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/19 21:19:57 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	tmp;

	if (fd < 0)
		return ;
	if (n < 0)
	{
		if (n == -2147483648)
		{
			write(fd, "-2147483648", 11);
			return ;
		}
		write(fd, "-", 1);
		n *= -1;
	}
	if (n < 10)
	{
		tmp = n + 48;
		write(fd, &tmp, 1);
		return ;
	}
	ft_putnbr_fd(n / 10, fd);
	tmp = n % 10 + 48;
	write(fd, &tmp, 1);
}
