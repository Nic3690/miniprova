/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:07:16 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/05 11:42:06 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_lexer	*reset_head(t_lexer *lexer)
{
	while (lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}

void	parser(char *str, t_envp_struct *envp_struct, char **envp)
{
	char		**temp;
	t_lexer		*lexer;

	lexer = NULL;
	temp = ft_split(str, ' ');
	find_quotes(temp);
	lexer = ft_list(temp);
	manage_string(&lexer);
	init_prev(&lexer);
	parser_env(&lexer, envp_struct);
	// print_lexer(&lexer);
	remove_all_quotes(&lexer);
	manage_heredoc(&lexer);
	split_command(&lexer, envp_struct, envp);
	lexer = reset_head(lexer);
	ft_free(temp);
	ft_free_lexer(&lexer);
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
	char	*temp_str;
	char	*string_one;
	char	*string_two;

	temp_str = ft_strdup(lexer->str);
	if (ft_strlen(lexer->str) > 0)
		string_one = temp_str;
	else
		string_one = lexer->token;
	if (ft_strlen(lexer->next->str) > 0)
		string_two = lexer->next->str;
	else
		string_two = lexer->next->token;
	free(lexer->str);
	lexer->str = ft_strjoin(string_one, string_two);
	free(temp_str);
	temp = lexer->next->next;
	free(lexer->next->str);
	free(lexer->next->token);
	free(lexer->next);
	lexer->next = temp;
}

void	print_lexer(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	while (*lexer)
	{
		if (ft_strlen((*lexer)->str) >= 1)
			printf("xxxxxxx%s\n", (*lexer)->str);
		if (ft_strlen((*lexer)->token) >= 1)
			printf("xxxxxxx%s\n", (*lexer)->token);
		*lexer = (*lexer)->next;
	}
	*lexer = head;
}
