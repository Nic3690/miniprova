/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:58:28 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/19 17:36:06 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	g_exit_code;

void	handle_sigint(int signal)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_code = signal;
}

void	handle_child(int signal)
{
	write (STDOUT_FILENO, "\n", 1);
	g_exit_code = signal;
	signal = 130;
}

void	handle_sigign(void)
{
	write (STDOUT_FILENO, "\n", 1);
	g_exit_code = 131;
}

void	reading(t_env *env, char **envp)
{
	char		*input;
	const char	*prompt;

	prompt = "\e[0;35m\e[0m";
	input = NULL;
	while (1)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
		input = readline(prompt);
		if (input == NULL)
			break ;
		else
		{
			parser(input, env, envp);
			add_history(input);
		}
		free(input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argv;
	g_exit_code = 0;
	env = split_envp(envp);
	if (argc != 1)
	{
		ft_free_env(env);
		return (0);
	}
	reading(env, envp);
	ft_free_env(env);
	return (0);
}
