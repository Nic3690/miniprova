/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:16:00 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/10 19:05:13 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser_env(t_lexer **lexer, t_env **env)
{
	int		i;
	t_lexer	*head_lexer;
	t_env	*head_env;

	i = 0;
	head_lexer = *lexer;
	head_env = *env;
	while ((*lexer))
	{
		if (count_quotes((*lexer)->str, '\'') != 2)
		{
			i = 0;
			while ((*lexer)->str[i])
			{
				if ((*lexer)->str[i] == '$')
					(*lexer)->str = search_value(lexer, *env);
				i++;
			}
		}
		(*lexer) = (*lexer)->next;
	}
	*lexer = head_lexer;
	*env = head_env;
}

int	search_map(t_env **env, char *str)
{
	int		index;
	t_env	*head;

	index = 0;
	head = *env;
	while (*env)
	{
		if (ft_strcmp((*env)->key, str) == 0)
		{
			*env = head;
			return (index);
		}
		index++;
		(*env) = (*env)->next;
	}
	*env = head;
	return (-1);
}

char	*search_value(t_lexer **lexer, t_env *env)
{
	t_env	*current;

	current = env;
	(*lexer)->str++;
	while (current)
	{
		if (ft_strcmp(current->key, (*lexer)->str) == 0)
			return (current->value);
		current = current->next;
	}
	return (ft_strdup(""));
}

