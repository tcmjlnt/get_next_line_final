/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjacquel <tjacquel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:12:28 by tjacquel          #+#    #+#             */
/*   Updated: 2024/09/26 20:30:57 by tjacquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
	int		fd;
	char	*str;

	fd = open("1char.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("%s", str);
		free(str);
	}
	printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));


	close (fd);
	free(str);
	return (0);
}
/*

#include "get_next_line.h"
#include <stdio.h>

int	main(void)
{
int fd = open("test.txt", O_RDONLY);
printf("%s", get_next_line(fd));
printf("%s", get_next_line(fd));
printf("%s", get_next_line(fd));
if (get_next_line(fd) == NULL)
	return (-1);
else
	printf("%s\n", get_next_line(fd));
close(fd);
return (0);
}
*/
