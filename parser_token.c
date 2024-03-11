/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 10:18:56 by nfurlani          #+#    #+#             */
/*   Updated: 2024/03/11 14:19:47 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_prev(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	while (*lexer && (*lexer)->next)
	{
		(*lexer)->next->prev = *lexer;
		*lexer = (*lexer)->next;
	}
	*lexer = head;
}

int	check_character(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

void	manage_token(t_lexer **lexer)
{
	char	**array;
	t_lexer	*new;
	t_lexer	*head;
	t_lexer	*next_node;

	head = *lexer;
	while (*lexer)
	{
		next_node = (*lexer)->next;
		if (ft_strlen((*lexer)->token) > 0)
		{
			array = ft_token_split((*lexer)->token);
			new = new_token(array);
			if (!(*lexer)->prev)
				head = new;
			new_list(*lexer, &new);
			free(array);
		}
		*lexer = next_node;
	}
	*lexer = head;
}

t_lexer	*new_token(char **array)
{
	t_lexer	*lexer;
	int		i;

	lexer = NULL;
	i = 0;
	while (array[i] != 0)
		i++;
	lexer = ft_list(i, array);
	init_prev(&lexer);
	return (lexer);
}

t_lexer	*new_list(t_lexer *current, t_lexer **new)
{
	t_lexer	*last_new;

	if (current->prev)
	{
		current->prev->next = *new;
		(*new)->prev = current->prev;
	}
	last_new = ft_lstlast(*new);
	if (current->next)
	{
		current->next->prev = last_new;
		last_new->next = current->next;
	}
	/*if (!current->prev)
	{
        if (current->str)
			free(current->str);
        if (current->token)
			free(current->token);
        free(current);
        return *new;
	}
	if (current->str)
		free(current->str);
    if (current->token)
		free(current->token);
    free(current);
	se scommento non funziona ma vanno liberati
	*/
	return (NULL);
}
