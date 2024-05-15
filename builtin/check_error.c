/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:10:09 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/16 00:00:33 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_token_error(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	if (ft_strcmp((*lexer)->token, "|") == 0)
		return (printf("syntax error near unexpected token '|'\n"));
	if ((*lexer)->token && !(*lexer)->next)
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
