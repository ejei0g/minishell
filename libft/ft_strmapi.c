/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 06:01:34 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/19 21:06:09 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*result;
	unsigned int	i;

	if (!s)
		return (NULL);
	i = 0;
	result = ft_strdup(s);
	if (result == NULL)
		return (NULL);
	while (result[i])
	{
		*(result + i) = f(i, result[i]);
		i++;
	}
	return (result);
}
