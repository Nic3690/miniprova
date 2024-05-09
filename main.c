/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:58:28 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/09 11:49:54 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void setup_signals()
{
	struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sa.sa_handler = handle_sigint;
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_sigint()
{
    write(STDOUT_FILENO, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
	exit_code = 1;
}

void	handle_child()
{
	write (STDOUT_FILENO, "\n", 1);
	exit_code = 130;
}

void	handle_sigign()
{
	write (STDOUT_FILENO, "\n", 1);
	exit_code = 131;
}

void	reading(t_envp_struct *envp_struct, char **envp)
{
	char		*input;
	char		*str;
	int			copy;
	const char *prompt;

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
			parser(str, envp_struct, envp);
			free(str);
			free(input);
		}
		close(copy);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envp_struct *envp_struct;

	exit_code = 0;
	envp_struct = malloc(sizeof(t_envp_struct));
	envp_struct->env = malloc(sizeof(t_env *));
	envp_struct->export = malloc(sizeof(t_export *));
	(void)argv;
	*(envp_struct->env) = split_envp(envp);
	using_history();
	if (argc != 1)
		return (0);
	*(envp_struct->export) = ft_lstcopy_env(*(envp_struct->env));
	bubble_sort_export(envp_struct);
	reading(envp_struct, envp);
	return (0);
}
