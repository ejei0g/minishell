/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 03:10:23 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/29 02:38:42 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy_s1;
	int		s1_len;
	int		i;

	i = 0;
	s1_len = ft_strlen(s1);
	copy_s1 = (char *)malloc(sizeof(char) * (s1_len + 1));
	if (copy_s1 == NULL)
		return (NULL);
	while (i < s1_len)
	{
		*(copy_s1 + i) = *(s1 + i);
		i++;
	}
	*(copy_s1 + i) = '\0';
	return (copy_s1);
}
