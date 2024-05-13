/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:58:28 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/13 17:59:47 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_signals(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = handle_sigint;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_sigint(int signal)
{
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_exit_code = signal;
}

void	handle_child(void)
{
	write (STDOUT_FILENO, "\n", 1);
	g_exit_code = 130;
}

void	handle_sigign(void)
{
	write (STDOUT_FILENO, "\n", 1);
	g_exit_code = 131;
}

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

	g_exit_code = 0;
	(void)argv;
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
