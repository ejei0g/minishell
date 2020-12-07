/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlcat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 23:28:54 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/09 18:18:45 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	i = 0;
	if (dstsize > dst_len)
	{
		while (i < dstsize - dst_len - 1 && src[i])
		{
			*(dst + dst_len + i) = *(src + i);
			i++;
		}
		*(dst + dst_len + i) = '\0';
		return (dst_len + src_len);
	}
	else
		return (dstsize + src_len);
}
