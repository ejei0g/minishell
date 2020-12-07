/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 02:37:03 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/19 21:20:21 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strjoin(char const *s1, char const *s2)
{
	char			*joined_str;
	unsigned int	jstr_len;
	unsigned int	i;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	jstr_len = ft_strlen(s1) + ft_strlen(s2);
	joined_str = (char *)malloc(sizeof(char) * (jstr_len + 1));
	if (joined_str == NULL)
		return (NULL);
	while (*s1)
	{
		*joined_str++ = *s1++;
	}
	while (*s2)
		*joined_str++ = *s2++;
	*joined_str = '\0';
	return (joined_str - jstr_len);
}
