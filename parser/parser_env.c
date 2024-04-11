/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 12:16:00 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/11 18:03:50 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser_env(t_lexer **lexer, t_env **env, t_export **export)
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
					(*lexer)->str = search_value(lexer, *env, *export);
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

int	search_map_export(t_export **export, char *str)
{
	int			index;
	t_export	*head;

	index = 0;
	head = *export;
	while (*export)
	{
		if (ft_strcmp((*export)->key, str) == 0)
		{
			*export = head;
			return (index);
		}
		index++;
		(*export) = (*export)->next;
	}
	*export = head;
	return (-1);
}

char	*search_value(t_lexer **lexer, t_env *env, t_export *export)
{
	t_env		*current;
	t_export	*current_export;

	current = env;
	current_export = export;
	(*lexer)->str++;
	while (current)
	{
		if (ft_strcmp(current->key, (*lexer)->str) == 0)
			return (current->value);
		else
		{
			while (current_export)
			{
				if (ft_strcmp(current_export->key, (*lexer)->str) == 0)
					return (current_export->value);
				current_export = current_export->next;
			}
		}
		current = current->next;
	}
	return (ft_strdup(""));
}
