/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfurlani <nfurlani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:58:28 by nfurlani          #+#    #+#             */
/*   Updated: 2024/03/11 16:45:59 by nfurlani         ###   ########.fr       */
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

t_utils	*copy_envp(char **envp)
{
	t_utils	*utils;
	int		count;
	int		j;

	j = 0;
	count = 0;
	while (envp[count])
		count++;
	utils = malloc(sizeof(t_utils));
	if (!utils)
		return (NULL);
	utils->envp = malloc (sizeof(char *) * (count + 1));
	if (!utils->envp)
	{
		free(utils);
		return (NULL);
	}
	j = 0;
	while (envp[j])
	{
		utils->envp[j] = ft_strdup(envp[j]);
		if (!utils->envp[j])
		{
			while (j > 0)
				free(utils->envp[--j]);
			free(utils->envp);
			free(utils);
			return (NULL);
		}
		j++;
	}
	utils->envp[j] = NULL;
	j = 0;
	while (utils->envp[j])
	{
		printf ("%s\n", utils->envp[j]);
		j++;
	}
	return (utils);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argv;
	copy_envp(envp);
	using_history();
	if (argc != 1)
		return (0);
	reading();
	return (0);
}
