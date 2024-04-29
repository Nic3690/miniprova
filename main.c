/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:58:28 by nfurlani          #+#    #+#             */
/*   Updated: 2024/04/29 21:26:18 by nfurlani         ###   ########.fr       */
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

void	reading(t_envp_struct *envp_struct, char **envp)
{
	char	*input;
	char	*str;
	int		copy;

	copy = dup(STDIN_FILENO);
	while (1)
	{
		dup2(copy, STDIN_FILENO);
		input = readline("\e[0;35mminishell> \e[0m");
		if (*input)
		{
			add_history(input);
			str = ft_strdup(input);
			parser(str, envp_struct, envp);
			free(input);
			ft_exit(str);
		}
		else
			break ;
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
