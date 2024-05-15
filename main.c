/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:58:28 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/15 22:42:05 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_exit_code;

void	reading(t_env *env, char **envp)
{
	char		*input;
	char		*str;
	int			copy;
	const char	*prompt;

	setup_signals();
	prompt = "\e[0;35mminishell> \e[0m";
	copy = dup(STDIN_FILENO);
	while (1)
	{
		dup2(copy, STDIN_FILENO);
		input = readline(prompt);
		if (input == NULL)
		{
			free(input);
			break ;
		}
		if (*input)
		{
			add_history(input);
			str = ft_strdup(input);
			parser(str, env, envp);
			free(str);
			free(input);
		}
		close(copy);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argv;
	g_exit_code = 0;
	env = split_envp(envp);
	using_history();
	if (argc != 1)
	{
		ft_free_env(env);
		return (0);
	}
	reading(env, envp);
	ft_free_env(env);
	return (0);
}
