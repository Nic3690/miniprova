/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:58:28 by nfurlani          #+#    #+#             */
/*   Updated: 2024/05/06 17:12:59 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_code = 0;

void setup_signals()
{
	struct sigaction sa;

    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);
}

void	handle_sigint()
{
    write(STDOUT_FILENO, "\n", 1);
    rl_replace_line("", 0);
    rl_on_new_line();
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
			(*envp_struct).exit_status = exit_code;
			free(str);
			free(input);
		}
		close(copy);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_envp_struct *envp_struct;

	envp_struct = malloc(sizeof(t_envp_struct));
	envp_struct->env = malloc(sizeof(t_env *));
	envp_struct->export = malloc(sizeof(t_export *));
	envp_struct->exit_status = 0;
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

/*
ctrl-C in an empty prompt should display a new line with a new prompt.
ctrl-\ in an empty prompt should not do anything.
ctrl-D in an empty prompt should quit minishell --> RELAUNCH!
ctrl-C in a prompt after you wrote some stuff should display a new line with a new prompt.
The buffer should be clean too. Press "Enter" to make sure nothing from the previous line is executed.
ctrl-D in a prompt after you wrote some stuff should not do anything.
ctrl-\ in a prompt after you wrote some stuff should not do anything.
Try ctrl-C after running a blocking command like cat without arguments or grep “something“.
Try ctrl-\ after running a blocking command like cat without arguments or grep “something“.
Try ctrl-D after running a blocking command like cat without arguments or grep “something“.
Repeat multiple times using different commands.
If something crashes, select the "crash" flag.
If something doesn't work, select the "incomplete work" flag.
*/