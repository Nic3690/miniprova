/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:09:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/11 14:09:42 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	builtin_env(t_lexer **lexer, t_env **env)
{
	t_env	*temp;

	temp = *env;
	if ((*lexer)->next == NULL)
	{
		if (ft_strcmp((*lexer)->str, "env") == 0)
		{
			while (temp)
			{
				printf ("%s=%s\n", temp->key, temp->value);
				temp = temp->next;
			}
			free(temp);
		}
	}
	else if ((*lexer)->next)
	{
		if (ft_strcmp((*lexer)->str, "env") == 0)
			print_env(lexer, env);
	}
}

void	print_env(t_lexer **lexer, t_env **env)
{
	int		i;
	t_env	*current;
	char	*temp_key;
	char	*temp_value;

	i = 0;
	current = *env;
	*lexer = (*lexer)->next;
	while ((*lexer)->str[i] != '=')
		i++;
	temp_key = ft_substr((*lexer)->str, 0, i);
	temp_value = ft_substr((*lexer)->str, i + 1, ft_strlen((*lexer)->str));
	i = 0;
	while (current)
	{
		if (ft_strcmp(current->key, temp_key) == 0)
			i = printf ("%s=%s\n", current->key, temp_value);
		else
			printf ("%s=%s\n", current->key, current->value);
		current = current->next;
	}
	if (i == 0)
		printf ("%s=%s\n", temp_key, temp_value); 
}
