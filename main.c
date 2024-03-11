/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:58:28 by nfurlani          #+#    #+#             */
/*   Updated: 2024/03/11 15:25:22 by nfurlani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char *str)
{
	char	*str2;
	int		r;

	str2 = "exit";
	r = ft_strcmp(str, str2);
	if (r == 0)
		exit(0);
	return (0);
}

void	reading(void)
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
			parser(str);
			ft_exit(str);
		}
		else
			break ;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	using_history();
	if (argc != 1)
		return (0);
	reading();
	return (0);
}
