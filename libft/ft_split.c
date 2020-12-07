/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeylee <jaeylee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 00:21:29 by jaeylee           #+#    #+#             */
/*   Updated: 2020/12/07 15:46:01 by jaeylee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_word(char const *s, char c)
{
	int		total;
	int		i;

	i = 0;
	total = 0;
	if (*s == 0 && c == 0)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c)
			total++;
		while (s[i] != c && s[i] != '\0')
			i++;
		while (s[i] == c && s[i] != '\0')
			i++;
	}
	return (total);
}

void	strs_free(char **strs, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	strs = NULL;
	return ;
}

int		word_length(char const *s, char c, int i)
{
	int	word_len;

	word_len = 0;
	while (s[i] != c && s[i] != 0)
	{
		word_len++;
		i++;
	}
	return (word_len);
}

int		alloc_word(char const *s, char c, char **strs)
{
	int		wd_index;
	int		i;
	int		wd_len;

	wd_index = 0;
	i = 0;
	if (*s == 0 && c == 0)
		return (0);
	while (s[i])
	{
		if (s[i] == c && s[i] != '\0')
			i++;
		else
		{
			wd_len = word_length(s, c, i);
			if (!(strs[wd_index] = ft_substr(s, i, wd_len)))
			{
				strs_free(strs, wd_index);
				return (-1);
			}
			i += wd_len;
			wd_index++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**split_strs;
	int		word_total;

	if (!s)
		return (NULL);
	word_total = count_word(s, c);
	if (!(split_strs = (char **)malloc(sizeof(char *) * (word_total + 1))))
		return (NULL);
	if (alloc_word(s, c, split_strs) == -1)
		return (NULL);
	*(split_strs + word_total) = NULL;
	return (split_strs);
}
