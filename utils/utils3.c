/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 20:54:19 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/05 11:19:47 by nfurlani         ###   ########.fr       */
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
	if (ft_strcmp(s1, ""))
		str[i++] = '\n';
	while (s2[n] != '\0')
		str[i++] = s2[n++];
	str[i] = '\0';
	return (str);
}

void remove_string_quotes(char *str) {
char *s_read = str;
    char *s_write = str;
    int in_single_quotes = 0;
    int in_double_quotes = 0;

    while (*s_read) {
        if (*s_read == '\"') {
            if (!in_single_quotes) {  // Check if not inside single quotes
                in_double_quotes = !in_double_quotes;  // Toggle double quotes status
                if (in_double_quotes || !in_double_quotes) {
                    // If entering or leaving double quotes, do not write quote to output
                    s_read++;
                    continue;
                }
            }
        } else if (*s_read == '\'') {
            if (!in_double_quotes) {  // Check if not inside double quotes
                in_single_quotes = !in_single_quotes;  // Toggle single quotes status
                if (in_single_quotes || !in_single_quotes) {
                    // If entering or leaving single quotes, do not write quote to output
                    s_read++;
                    continue;
                }
            }
        }
        // Copy the character if it's not a skipped quote
        *s_write++ = *s_read;
        s_read++;
    }
    *s_write = '\0';  // Null-terminate the modified string.
}

void remove_all_quotes(t_lexer **lexer) {
    t_lexer *head = *lexer;

    while (*lexer) {
        if ((*lexer)->str && strlen((*lexer)->str) > 0) {
            remove_string_quotes((*lexer)->str);
        }
        *lexer = (*lexer)->next;
    }
    *lexer = head;
}


char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
