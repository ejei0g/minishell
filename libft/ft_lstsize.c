/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 03:14:46 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/15 00:21:59 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	t_list	*temp;
	int		result;

	result = 1;
	temp = lst;
	if (lst == NULL)
		return (0);
	while (temp->next != NULL)
	{
		result++;
		temp = temp->next;
	}
	return (result);
}
