/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dleaves <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:28:03 by dleaves           #+#    #+#             */
/*   Updated: 2022/03/19 19:41:50 by dleaves          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

static int	to_find(char const *set, char c)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*res;

	if (!s1 || !set)
		return (0);
	i = 0;
	while (s1[i] && to_find(set, s1[i]))
		i++;
	len = ft_strlen(s1 + i);
	if (len != 0)
		while (s1[len + i - 1] && to_find(set, s1[len + i - 1]))
			len--;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (0);
	ft_strncpy(res, s1 + i, len);
	res[len] = '\0';
	return (res);
}
