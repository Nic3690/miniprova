/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:07:16 by nfurlani          #+#    #+#             */
/*   Updated: 2024/03/11 12:47:36 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	conv_lexer(char *str)
{
	char	**temp;
	t_lexer	*lexer;
	int		i;

	i = 0;
	lexer = NULL;
	temp = ft_split(str, ' ');
	find_quotes(temp);
	/*a questo punto ho temp modificato*/
	while (temp[i] != 0)
		i++;
	lexer = ft_list(i, temp);
	manage_string(&lexer);
	lexer_index(&lexer);
}
/*dove ritorno **lexer?????*/

void	manage_string(t_lexer **lexer)
{
	while (*lexer && (*lexer)->next)
	{
		if (ft_strchr((*lexer)->str, '\'') || ft_strchr((*lexer)->str, '"'))
			join_string(*lexer);
		if ((count_quotes((*lexer)->str, '"') == 2 && (*lexer)->next != 0)
			|| (count_quotes((*lexer)->str, '\'') == 2 && (*lexer)->next != 0))
			*lexer = (*lexer)->next;
		else
			*lexer = (*lexer)->next;
	}
}

void	join_string(t_lexer *lexer)
{
	t_lexer	*temp;

	lexer->str = ft_strjoin(lexer->str, lexer->next->str);
	temp = lexer->next->next;
	free(lexer->next);
	lexer->next = temp;
}

void	lexer_index(t_lexer **lexer)
{
	printf ("%p\n", (*lexer));
	printf ("%p\n", (*lexer)->next);
	while (*lexer && (*lexer)->next)
	{
		if (ft_strchr((*lexer)->str, ' '))
		{
			(*lexer)->index += 1;
		}
		(*lexer) = (*lexer)->next;
	}
}
