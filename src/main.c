/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mramiro- <mramiro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:14:07 by mramiro-          #+#    #+#             */
/*   Updated: 2024/04/23 18:10:54 by mramiro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_error(char *msg)
{
	printf("%s\n", msg);
	exit(1);
}

char **parse(char *input)
{
	char **tokens;

	tokens = ft_split(input, ' ');
	return (tokens);
}

int	change_dir(char *path)
{
	if (path)
	{
		if (chdir(path) == -1)
			handle_error("Error: cd failed");
	}
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	pid_t	child_pid;
	int		child_status;
	char	*path;
	char	**tokens;

	argc++;
	while (1)
	{
		line = readline("$ ");
		if (!line)
			(printf("\n"), exit(0));
		add_history(line);
		tokens = parse(line);
		if (tokens == NULL || tokens[0] == NULL)
			continue ;
		if (ft_strncmp(tokens[0], "cd", 2) == 0)
			change_dir(tokens[1]);
		else
		{
			child_pid = fork();
			argv = NULL;
			path = cmd_find(tokens[0], envp);
			if (child_pid == 0)
				(execve(path, tokens, envp), exit(1));
			else
				(wait(&child_status));
		}
		free_str_array(tokens);
	}
	return (0);
}
