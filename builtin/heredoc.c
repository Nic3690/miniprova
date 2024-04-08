/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 20:53:05 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/05 16:36:27 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	manage_heredoc(t_lexer **lexer)
{
	char	*input;
	t_lexer	*head;
	char	*str;

	head = *lexer;
	while ((*lexer) && (*lexer)->next)
	{
		if (ft_strcmp((*lexer)->token, "<<") == 0)
		{
			str = ft_strdup((*lexer)->next->str);
			(*lexer)->next->str = "";
			while (1)
			{
				input = readline("heredoc> ");
				if (*input)
				{
					if (ft_strcmp(input, str) == 0)
					{
						free((*lexer)->token);
						(*lexer)->token = "<<";
						break ;
					}
					(*lexer)->next->str = ft_strjoin_heredoc((*lexer)->next->str, input);
				}
			}
		}
		*lexer = (*lexer)->next;
	}
	*lexer = head;
}

/*gestire cd senza argomenti*/
