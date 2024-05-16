/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:04:24 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/16 18:46:08 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_superlen(int len, int len2)
{
	char	*sub;

	if (len2 < len)
		sub = (char *)malloc(sizeof(char) * (len2 + 1));
	else
		sub = (char *)malloc(sizeof(char) * (len + 1));
	return (sub);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	len2;
	int		n;
	int		i;
	int		j;

	len2 = 1;
	n = start;
	if (!s)
		return (NULL);
	if (start >= (unsigned int)ft_strlen(s))
		return (NULL);
	i = 0;
	while (s[start++] != '\0')
		len2++;
	sub = ft_superlen(len, len2);
	if (!sub)
		return (NULL);
	j = n;
	while (s[n] != '\0' && (size_t)n < len + j)
		sub[i++] = s[n++];
	sub[i] = '\0';
	return (sub);
}

int	get_word(char *s, char c)
{
	int	ret;

	ret = 0;
	while (*s)
	{
		if (*s != c)
		{
			++ret;
			while (*s && *s != c)
				++s;
		}
		else
			++s;
	}
	return (ret);
}

char	**ft_split(char *s, char c)
{
	char	**ret;
	size_t	i;
	size_t	len;
	
	i = 0;
	ret = ft_calloc(10000, sizeof(char *));
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && (*s != c) && ++len)
				++s;
			ret[i++] = ft_substr(s - len, 0, len);
		}
		else
			++s;
	}
	ret[i] = 0;
	return (ret);
}
