/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:53:40 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/12 16:54:14 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	builtin_cd(t_lexer **lexer)
{
	char	cwd[1024];

	if (ft_strcmp((*lexer)->str, "cd") == 0)
	{
		if (!(*lexer)->next)
			chdir(getenv("HOME"));
		else if (chdir((*lexer)->next->str) != 0)
		{
			perror((*lexer)->next->str);
			exit_code = 1;
			return (1);
		}
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			perror((*lexer)->next->str);
			exit_code = 1;
			return (1);
		}
	}
	return (1);
}

int	builtin_pwd(t_lexer **lexer)
{
	char	cwd[1024];

	if (ft_strcmp((*lexer)->str, "pwd") == 0)
	{
		if (getcwd(cwd, sizeof(cwd)))
		{
			printf ("%s\n", cwd);
			return (1);
		}
		else
		{
			perror((*lexer)->str);
			exit_code = 1;
			return (1);
		}
	}
	return (1);
}

int	builtin_echo(t_lexer **lexer)
{
	int	flag;

	flag = 1;
	if (ft_strcmp((*lexer)->str, "echo") == 0)
	{
		if (!(*lexer)->next || (*lexer)->next->str == NULL)
			return (printf ("\n"));
		*lexer = (*lexer)->next;
		if (*lexer && ft_strcmp((*lexer)->str, "-n") == 0)
		{
			flag = 0;
			*lexer = (*lexer)->next;
		}
		while (*lexer && (*lexer)->next)
		{
			printf ("%s ", (*lexer)->str);
			*lexer = (*lexer)->next;
		}
		if (*lexer)
			printf ("%s", (*lexer)->str);
		if (flag)
			printf ("\n");
	}
	return (1);
}

int	builtin_unset(t_lexer **lexer, t_env *env)
{
	t_env		*head_env;

	head_env = env;
	if (del_first_env(lexer, env))
		return (1);
	if (ft_strcmp((*lexer)->str, "unset") == 0)
	{
		unset_env(lexer, env);
	}
	env = head_env;
	return (1);
}

int	unset_env(t_lexer **lexer, t_env *env)
{
	t_env	*prev_env;
	t_env	*head;

	prev_env = NULL;
	head = env;
	if (!del_last_env(lexer, env))
		return (0);
	env = head;
	while (env != NULL && ft_strcmp(env->key, (*lexer)->next->str) != 0)
	{
		prev_env = env;
		env = env->next;
	}
	if (env == NULL)
		return (0);
	prev_env->next = env->next;
	free(env->key);
	free(env->value);
	free(env);
	return (0);
}

int	del_first_env(t_lexer **lexer, t_env *env)
{
	t_env	*temp;

	temp = env;
	if (temp != NULL && ft_strcmp(temp->key, (*lexer)->next->str) == 0)
	{
    	temp = env->next;
        free(env->key);
        free(env->value);
        free(env);
		env = temp;
		return (1);
    }
	return (0);
}

int	del_last_env(t_lexer **lexer, t_env *env)
{
	t_env	*temp;

	temp = env;
	while (env && env->next)
	{
    	temp = env->next;
		if (ft_strcmp(env->key, (*lexer)->next->str) == 0)
		{
			free(env->key);
			free(env->value);
			free(env);
			env = temp;
			return(0);
		}
		env = env->next;
	}
	return (1);
}
