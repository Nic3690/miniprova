/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 14:40:08 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/18 14:59:17 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_check_all_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] == '\"') || (str[i] == '\''))
			return (1);
		i++;
	}
	return (0);
}

int	check_token_error(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	if (ft_strcmp((*lexer)->token, "|") == 0)
		return (printf("syntax error near unexpected token '|'\n"));
	if ((*lexer)->token && !(*lexer)->next)
		return (printf("syntax error near unexpected token 'newline'\n"));
	if ((*lexer)->str && (*lexer)->next && (*lexer)->next->token && !(*lexer)->next->next)
		return (printf("syntax error near unexpected token 'newline'\n"));
	while (*lexer)
	{
		if ((*lexer)->next && (*lexer)->token && (*lexer)->next->token)
		{
			printf("syntax error near unexpected token '%s'\n", (*lexer)->token);
			*lexer = head;
			return (1);
		}
		*lexer = (*lexer)->next;
	}
	*lexer = head;
	return (0);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
