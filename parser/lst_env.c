/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 17:48:47 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/14 11:50:02 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*split_envp(char **envp)
{
	char	*key;
	char	*value;
	int		count;
	int		temp;
	t_env	*env;

	env = NULL;
	while (*envp)
	{
		count = 0;
		while ((*envp)[count] != '=' && (*envp)[count] != '\0')
			count++;
		key = ft_substr(*envp, 0, count);
		count++;
		temp = ft_strlen(*envp);
		value = ft_substr(*envp, count, temp);
		ft_lstadd_back_env(&env, ft_list_env(key, value));
		envp++;
	}
	return (env);
}

t_env	*ft_list_env(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (new == NULL)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = ft_lstlast_env(*lst);
	temp->next = new;
}

t_env	*ft_lstlast_env(t_env *lst)
{
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

int	search_map_env(t_env *env, char *str)
{
	int			index;
	t_env		*head;

	index = 0;
	head = env;
	while (env)
	{
		if (ft_strcmp(env->key, str) == 0)
		{
			env = head;
			return (index);
		}
		index++;
		env = env->next;
	}
	env = head;
	return (-1);
}
