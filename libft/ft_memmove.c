/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 17:00:04 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/29 02:41:00 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	buffer;
	size_t			i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < len)
	{
		if (dst > src)
		{
			buffer = *(unsigned char *)(src + len - i - 1);
			*(unsigned char *)(dst + len - i - 1) = buffer;
		}
		else
		{
			buffer = *(unsigned char *)(src + i);
			*(unsigned char *)(dst + i) = buffer;
		}
		i++;
	}
	return ((void *)dst);
}
