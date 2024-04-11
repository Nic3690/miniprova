/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:07:16 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/11 18:08:13 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser(char *str, t_env **env, t_export **export)
{
	char		**temp;
	t_lexer		*lexer;
	int			i;

	i = 0;
	lexer = NULL;
	temp = ft_split(str, ' ');
	find_quotes(temp);
	while (temp[i] != 0)
		i++;
	lexer = ft_list(i, temp);
	manage_string(&lexer);
	init_prev(&lexer);
	manage_token(&lexer);
	lexer_index(&lexer);
	parser_env(&lexer, env, export);
	manage_heredoc(&lexer); // spostare dopo e modificare
	remove_all_quotes(&lexer);
	builtin_cd(&lexer);
	builtin_pwd(&lexer);
	builtin_echo(&lexer);
	builtin_env(&lexer, env);
	builtin_export(&lexer, export);
	// split_command(&lexer);
	// print_lexer(&lexer);
}

void	manage_string(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	while (*lexer && (*lexer)->next)
	{
		if (count_quotes((*lexer)->str, '\'') == 1
			|| ft_strchr((*lexer)->str, '"')
			|| count_quotes((*lexer)->token, '\'') == 1
			|| ft_strchr((*lexer)->token, '"'))
		{
			join_string(*lexer);
			if ((count_quotes((*lexer)->str, '"') == 2
					&& (*lexer)->next != NULL)
				|| (count_quotes((*lexer)->str, '\'') == 2
					&& (*lexer)->next != NULL))
				*lexer = (*lexer)->next;
		}
		else
			*lexer = (*lexer)->next;
	}
	*lexer = head;
}

void	join_string(t_lexer *lexer)
{
	t_lexer	*temp;
	char	*string_one;
	char	*string_two;

	if (ft_strlen(lexer->str) > 0)
		string_one = lexer->str;
	else
		string_one = lexer->token;
	if (ft_strlen(lexer->next->str) > 0)
		string_two = lexer->next->str;
	else
		string_two = lexer->next->token;
	lexer->str = ft_strjoin(string_one, string_two);
	temp = lexer->next->next;
	free(lexer->next);
	lexer->next = temp;
}

void	lexer_index(t_lexer **lexer)
{
	t_lexer	*head;
	int		i;

	head = *lexer;
	i = 0;
	while (*lexer)
	{
		(*lexer)->index = i;
		i++;
		(*lexer) = (*lexer)->next;
	}
	*lexer = head;
}

void	print_lexer(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	while (*lexer)
	{
		if (ft_strlen((*lexer)->str) >= 1)
			printf("%d - %s\n", (*lexer)->index, (*lexer)->str);
		if (ft_strlen((*lexer)->token) >= 1)
			printf("%d - %s\n", (*lexer)->index, (*lexer)->token);
		*lexer = (*lexer)->next;
	}
	*lexer = head;
}
