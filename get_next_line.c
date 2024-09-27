/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 18:04:15 by tjacquel          #+#    #+#             */
/*   Updated: 2024/09/27 16:49:08 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_line(int fd, char *string, char *buffer)
{
	char	*tmp;
	int		bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(string), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (string == NULL)
			string = ft_strdup("");
		if (string == NULL)
			return (NULL);
		tmp = string;
		string = ft_strjoin(tmp, buffer);
		free (tmp);
		if (!string)
			return (NULL);
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
	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
		i++;
	line = malloc((i + 1 + (string[i] == '\n')) * sizeof(char));
	if (!line)
	{
		free (string);
		return (NULL);
	}
	i = 0;
	while (string[i] != '\0' && string[i] != '\n')
	{
		line[i] = string[i];
		i++;
	}
	if (string[i] == '\n')
		line[i++] = '\n';
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
	new_stash = malloc((ft_strlen(string) - i) * sizeof(char));
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

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	stash = ft_read_line(fd, stash, buffer);
	free(buffer);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = ft_update_stash(stash);
	return (line);
}
