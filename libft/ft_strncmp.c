/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:21:25 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/07 12:22:21 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	temp_s1;
	unsigned char	temp_s2;

	i = 0;
	while (i < n && (*(s1 + i) || *(s2 + i)))
	{
		if (*(s1 + i) == *(s2 + i))
			i++;
		else
		{
			temp_s1 = *(s1 + i);
			temp_s2 = *(s2 + i);
			return (temp_s1 - temp_s2);
		}
	}
	return (0);
}
