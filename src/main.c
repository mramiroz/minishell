/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mramiro- <mramiro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:14:07 by mramiro-          #+#    #+#             */
/*   Updated: 2024/04/16 16:56:12 by mramiro-         ###   ########.fr       */
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

void	handle_sigint(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	pid_t	child_pid;
	int		child_status;
	char	*path;
	char	**tokens;

	signal(SIGINT, handle_sigint);
	argc++;
	while (1)
	{
		line = readline("$ ");
		if (!line)
			(printf("\n"), exit(0));
		add_history(line);
		tokens = parse(line);
		child_pid = fork();
		argv = NULL;
		path = cmd_find(tokens[0], envp);
		if (child_pid == 0)
			(execve(path, tokens, envp), exit(1));
		else
			(wait(&child_status));
		free_str_array(tokens);
	}
	return (0);
}
