/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzenz <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 10:03:46 by tzenz             #+#    #+#             */
/*   Updated: 2019/09/16 18:44:00 by tzenz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	char	*start;

	if (!s1 && !s2)
		return (NULL);
	result = ft_strnew((s1 ? ft_strlen(s1) : 0) + (s2 ? ft_strlen(s2) : 0));
	if ((start = result))
	{
		if (s1)
			while (*s1)
				*result++ = *s1++;
		if (s2)
			while (*s2)
				*result++ = *s2++;
		*result = '\0';
	}
	return (start);
}
