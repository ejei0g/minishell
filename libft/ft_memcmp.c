/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:23:03 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/07 12:17:26 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*uc_s1;
	const unsigned char	*uc_s2;
	size_t				i;

	uc_s1 = s1;
	uc_s2 = s2;
	i = 0;
	while (i < n)
	{
		if (*(uc_s1 + i) != *(uc_s2 + i))
			return (*(uc_s1 + i) - *(uc_s2 + i));
		i++;
	}
	return (0);
}
