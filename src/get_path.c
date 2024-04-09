/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mramiro- <mramiro-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:14:52 by mramiro-          #+#    #+#             */
/*   Updated: 2024/04/09 15:17:07 by mramiro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*find_path(char **envp)
{
	int		i;
	char	*path;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*cmd_find(char *cmd, char **envp)
{
	char	*path;
	char	**path_split;
	char	*cmd_path;
	int		i;

	i = 0;
	path = find_path(envp);
	if (path == NULL)
		handle_error("Error: PATH not found");
	path_split = ft_split(path, ':');
	while (path_split[i] != NULL)
	{
		cmd_path = ft_strjoin(ft_strjoin(path_split[i], "/"), cmd);
		if (access(cmd_path, F_OK) == 0)
		{
			free_str_array(path_split);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	free_str_array(path_split);
	return (NULL);
}
