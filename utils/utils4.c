/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:54:19 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/08 15:19:05 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count && size >= 65536)
		return (0);
	p = malloc(count * size);
	if (p == 0)
		return (0);
	ft_bzero(p, count * size);
	return (p);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = '\0';
		i++;
	}
	return ;
}

char	*ft_strjoin_heredoc(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (!s1 || !s2)
		return (0);
	str = malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!str)
		return (0);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\n';
	i++;
	while (s2[n] != '\0')
		str[i++] = s2[n++];
	str[i] = '\0';
	return (str);
}

void remove_all_quotes(t_lexer **lexer)
{
	t_lexer	*head;
	char	*s_read;
	char	*s_write;

	head = *lexer;
    while (*lexer)
	{
        s_read = (*lexer)->str;
        s_write = (*lexer)->str;

        while (*s_read)
		{
            if (*s_read != '\'' && *s_read != '\"')
                *s_write++ = *s_read;
            s_read++;
        }
        *s_write = '\0';
        *lexer = (*lexer)->next;
    }
	*lexer = head;
}
