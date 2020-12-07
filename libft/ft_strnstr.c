/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:02:26 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/09 18:47:49 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!*(needle + i))
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		if (ft_strncmp(haystack + i, needle, ft_strlen(needle)) == 0)
		{
			if (i + ft_strlen(needle) <= len)
				return (char *)(haystack + i);
		}
		i++;
	}
	return (NULL);
}
