/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperedny <gperedny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:40:52 by gperedny          #+#    #+#             */
/*   Updated: 2025/06/13 19:16:13 by gperedny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*return_buffer(char *buffer, char *storage, int index);

char	*get_next_line(int fd)
{
	static char	storage[BUFFER_SIZE + 1];
	int			reading;
	char		*time_buffer;
	int			i;

	i = 0;
	while (storage[i] != '\0')
	{
		if (storage[i] == '\n' || storage[i] == '\0')
		{
			printf("%s\n", storage);
			time_buffer = return_buffer(ft_strdup((const char *)storage),
					storage, i);
			break ;
		}
		i++;
	}
	if (time_buffer[i] == '\n')
		return (time_buffer);
	time_buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!time_buffer)
		return (NULL);
	reading = read(fd, time_buffer, BUFFER_SIZE);
	if (reading <= 0)
		return (NULL);
	i = 0;
	while (time_buffer)
	{
		if (time_buffer[i] == '\n' || time_buffer[i] == '\0')
		{
			printf("%s\n", storage);
			return (return_buffer(time_buffer, storage, i));
		}
		i++;
	}
	return (time_buffer);
}
char	*return_buffer(char *buffer, char *storage, int index)
{
	char	*result;
	int		j;

	if (buffer[index] == '\n')
		index++;
	j = 0;
	result = malloc((index + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (j < index)
	{
		result[j] = buffer[j];
		j++;
	}
	result[j] = '\0';
	j = 0;
	while (buffer[index + j] != '\0')
	{
		storage[j] = buffer[index + j];
		j++;
	}
	storage[j] = '\0';
	free(buffer);
	// printf("%s\n", storage);
	return (result);
}
int	main(void)
{
	int fd;
	int count;
	char *nxln;

	// char buffer[2];
	count = 0;
	fd = open("gnl.txt", O_RDONLY);
	while (1)
	{
		nxln = get_next_line(fd);
		if (nxln == NULL)
			break ;
		count++;
		printf("%d %s\n", count, nxln);
		free(nxln);
		nxln = NULL;
	}
	return (0);
}