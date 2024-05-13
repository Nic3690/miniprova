/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 11:09:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/12 17:41:23 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_env(t_lexer **lexer, t_env *env)
{
	t_env	*temp;

	temp = env;
	
	if ((*lexer)->next == NULL)
	{
		if (ft_strcmp((*lexer)->str, "env") == 0)
		{
			while (temp && temp->key)
			{
				printf ("%s=%s\n", temp->key, temp->value);
				temp = temp->next;
			}
			// free(temp);
		}
	}
	else if ((*lexer)->next)
	{
		printf("%s: %s: No such file or directory\n", (*lexer)->str, (*lexer)->next->str);
		exit_code = 127;
	}
	return (1);
}

t_env   *ft_lstcopy_env(t_env *env)
{
    t_env	*new_list;
    t_env	*head;

	new_list = NULL;
	head = env;
    while (env != NULL)
    {
        ft_lstadd_back_env(&new_list, ft_list_env(ft_strdup(env->key), ft_strdup(env->value)));
        env = env->next;
    }
	env = head;
    return (new_list);
}
