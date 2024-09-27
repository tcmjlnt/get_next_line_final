/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:04:15 by tjacquel          #+#    #+#             */
/*   Updated: 2024/09/27 10:51:14 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>


char	*ft_read_line(int fd, char *string, char *buffer)
{
	char	*tmp;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(string);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (string == NULL)
			string = ft_strdup("");
		tmp = string;
		string = ft_strjoin(tmp, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (string);
}

char	*ft_extract_line(char *string)
{
	char	*line;
	int		i;

	if (!string || !*string)
		return (NULL);
	//i = 0;
	//while (string[i] != '\0' && string[i] != '\n')
	//	i++;
	line = malloc((ft_strlen(string) + 2) * sizeof(char));
	// j'hesite entre malloc (ft_strlen + 2) ou (i + 2)
	// a priori c'est pas le meme chose mais les deux ont l'air de fonctionner
	if (!line)
		return (NULL);
	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
	{
		line[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_update_stash(char *string)
{
	char	*new_stash;
	int		i;
	int		j;

	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	if (string[i] == '\0')
	{
		free(string);
		return (NULL);
	}
	new_stash = malloc((ft_strlen(string) - i + 1) * sizeof(char));
	if (!new_stash)
		return (NULL);
	i++;
	j = 0;
	while (string[i] != '\0')
		new_stash[j++] = string[i++];
	new_stash[j] = '\0';
	free(string);
	return (new_stash);
}

// Main function: Get the next line from the file descriptor
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		return (NULL);
	}
	stash = ft_read_line(fd, stash, buffer);
	free(buffer);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	stash = ft_update_stash(stash);
	return (line);
}
