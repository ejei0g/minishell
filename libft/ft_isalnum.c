/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isalnum.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:10:10 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/19 21:21:01 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (64 < c && c < 91)
		return (8);
	if (96 < c && c < 123)
		return (8);
	if (47 < c && c < 58)
		return (8);
	return (0);
}
