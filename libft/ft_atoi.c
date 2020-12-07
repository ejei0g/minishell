/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 01:24:55 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/29 16:13:29 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_space(char c)
{
	if ((8 < c && c < 14) || c == ' ')
		return (1);
	return (0);
}

int	is_numeric(char c)
{
	if (47 < c && c < 58)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int i;
	int sign;
	int sum;

	sum = 0;
	sign = 1;
	i = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (is_numeric(str[i]))
	{
		sum = sum * 10;
		sum = sum + str[i] - 48;
		i++;
	}
	return (sum * sign);
}
