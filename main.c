/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:58:28 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/12 17:18:52 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *str)
{
	char	*str2;
	int		r;

	str2 = "exit";
	r = ft_strcmp(str, str2);
	free(str);
	if (r == 0)
		exit(0);
	return (0);
}

void	reading(t_env **env, t_export **export, char **envp)
{
	char	*input;
	char	*str;

	while (1)
	{
		input = readline("minishell> ");
		if (*input)
		{
			add_history(input);
			str = ft_strdup(input);
			parser(str, env, export, envp);
			ft_exit(str);
		}
		else
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;
	t_export	*export;

	(void)argv;
	env = split_envp(envp);
	using_history();
	if (argc != 1)
		return (0);
	export = ft_lstcopy_env(env);
	bubble_sort_export(&export);
	reading(&env, &export, envp);
	return (0);
}
