/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:54:19 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/19 16:48:36 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	remove_string_quotes(char *str)
{
	char	*s_read;
	char	*s_write;
	int		single_quotes;
	int		double_quotes;

	s_read = str;
	s_write = str;
	single_quotes = 0;
	double_quotes = 0;
	check_all(&single_quotes, &double_quotes, s_read, s_write);
}

void	remove_all_quotes(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	while (*lexer)
	{
		if ((*lexer)->str && ft_strlen((*lexer)->str) > 0)
			remove_string_quotes((*lexer)->str);
		*lexer = (*lexer)->next;
	}
	*lexer = head;
}

void	check_all(int *one, int *two, char *s_read, char *s_write)
{
	while (*s_read)
	{
		if (*s_read == '\"')
		{
			if (!(*one))
				(*two) = !(*two);
			else
				*s_write++ = *s_read;
		}
		else if (*s_read == '\'')
		{
			if (!(*two))
				(*one) = !(*one);
			else
				*s_write++ = *s_read;
		}
		else if (*s_read != '\'' && *s_read != '\"')
			*s_write++ = *s_read;
		s_read++;
	}
	*s_write = '\0';
}
