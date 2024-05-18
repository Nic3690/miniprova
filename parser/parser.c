/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 14:07:16 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/18 15:56:34 by nfurlani         ###   ########.fr       */
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
	temp = ft_split(str);
	find_quotes(temp);
	lexer = ft_list(temp);
	init_prev(&lexer);
	move_redirection(&lexer);
	if (check_token_error(&lexer) == 0)
	{
		parser_env(&lexer, env);
		remove_all_quotes(&lexer);
		manage_heredoc(&lexer);
		if (ft_strcmp(lexer->str, "export") == 0
			|| ft_strcmp(lexer->str, "unset") == 0 || ft_strcmp(lexer->str, "cd") == 0)
			manage_builtin(&lexer, env);
		else
			split_command(&lexer, env, envp);
		lexer = reset_head(lexer);
	}
	ft_free(temp);
	ft_free_lexer(&lexer);
}

int	check_nodes(t_lexer **lexer)
{
	if (!(*lexer)->next)
        return (1);
	if (((*lexer)->next && (*lexer)->next->token) || !(*lexer)->next->next)
		return (1);
	return (0);
}

void	move_redirection(t_lexer **lexer)
{
	t_lexer	*current;
	t_lexer	*redirection;
	t_lexer	*next_node;
	t_lexer	*to_save;

	if (check_nodes(lexer) == 1)
		return ;
    current = *lexer;
    if (ft_check_token(current->token))
	{
        while (current->next != NULL)
            current = current->next;
        redirection = *lexer;
		to_save = current->next;
        next_node = redirection->next;
        *lexer = next_node->next;
        if (current->prev != NULL)
            current->next = redirection;
        redirection->prev = current;
        if (to_save == NULL)
            redirection->next->next = NULL;
        else
            redirection->next->next = to_save;
    }
	init_prev(lexer);
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
	if (!*str)
		return (1);
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
