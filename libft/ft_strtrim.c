/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 03:13:02 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/30 01:24:21 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_found_char(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim_str;
	char	*start_ptr;
	char	*end_ptr;
	size_t	trim_len;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	start_ptr = (char *)s1;
	end_ptr = (char *)s1 + ft_strlen(s1) - 1;
	trim_len = ft_strlen(s1);
	i = 0;
	while (ft_found_char(*start_ptr++, set))
		trim_len--;
	start_ptr--;
	while (ft_found_char(*end_ptr--, set) && *start_ptr)
		trim_len--;
	if (!(trim_str = ft_substr(start_ptr, 0, trim_len)))
		return (NULL);
	return (trim_str);
}
