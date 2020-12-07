/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/13 03:17:54 by jaeylee           #+#    #+#             */
/*   Updated: 2020/04/19 21:25:01 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*target;
	t_list	*temp;

	if (!lst || !del)
		return ;
	target = *lst;
	temp = target;
	while (target != NULL)
	{
		temp = target->next;
		del(target->content);
		free(target);
		target = temp;
	}
	*lst = NULL;
	return ;
}
