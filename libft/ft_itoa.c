/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 20:57:20 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/19 21:21:35 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_int_len(int n)
{
	if (n == 0)
		return (0);
	else
		return (ft_int_len(n / 10) + 1);
}

void	push_str(char *origin, int n, int len)
{
	int				i;
	int				minus;
	unsigned int	num;

	num = n;
	minus = 0;
	i = 0;
	if (n < 0)
	{
		origin[0] = '-';
		num = num * -1;
		minus = 1;
	}
	while (minus < len - i)
	{
		origin[len - i - 1] = num % 10 + 48;
		num = num / 10;
		i++;
	}
}

char	*ft_itoa(int n)
{
	char	*result;
	int		res_len;

	if (n > 0)
		res_len = ft_int_len(n);
	else
		res_len = ft_int_len(n) + 1;
	result = (char *)malloc(sizeof(char) * res_len + 1);
	if (result == NULL)
		return (NULL);
	push_str(result, n, res_len);
	result[res_len] = '\0';
	return (result);
}
