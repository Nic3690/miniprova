/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:07:16 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/18 12:14:58 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	parser(char *str, t_env *env, char **envp)
{
	char		**temp;
	t_lexer		*lexer;

	lexer = NULL;
	if (check_spaces(str) == 0)
		return ;
	temp = ft_split(str, ' ');
	find_quotes(temp);
	lexer = ft_list(temp);
	// print_lexer(&lexer);
	if (check_token_error(&lexer) == 0)
	{
		init_prev(&lexer);
		parser_env(&lexer, env);
		remove_all_quotes(&lexer);
		manage_heredoc(&lexer);
		split_command(&lexer, env, envp);
		lexer = reset_head(lexer);
	}
	ft_free(temp);
	ft_free_lexer(&lexer);
}

t_lexer	*reset_head(t_lexer *lexer)
{
	while (lexer->prev)
		lexer = lexer->prev;
	return (lexer);
}

int	check_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

void	print_lexer(t_lexer **lexer)
{
	t_lexer	*head;

	head = *lexer;
	while (*lexer)
	{
		if ((*lexer)->str)
			printf("Str: %s\n", (*lexer)->str);
		if ((*lexer)->token)
			printf("Token: %s\n", (*lexer)->token);
		*lexer = (*lexer)->next;
	}
	*lexer = head;
}
