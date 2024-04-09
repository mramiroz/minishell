/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mramiro- <mramiro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:14:07 by mramiro-          #+#    #+#             */
/*   Updated: 2024/04/09 15:39:44 by mramiro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	pid_t	child_pid;
	int		child_status;
	char	*path;

	argc++;
	while (1)
	{
		line = readline("$ ");
		add_history(line);
		argv[0] = line;
		argv[1] = NULL;
		child_pid = fork();
		path = cmd_find(argv[0], envp);
		if (child_pid == 0)
		{
			execve(path, argv, NULL);
			printf("Command not found\n");
			exit(1);
		}
		else
			wait(&child_status);
	}
	return (0);
}
