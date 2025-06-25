/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperedny <gperedny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 13:02:34 by gperedny          #+#    #+#             */
/*   Updated: 2025/06/16 13:35:49 by gperedny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_save(char *keeper, char *storage)
{
	char	*line;
	size_t	i;
	size_t	j;
	size_t	k;

	j = 0;
	i = 0;
	if (!keeper || !*keeper)
		return (NULL);
	while (keeper[j] && keeper[j] != '\n')
		j++;
	if (keeper[j] == '\n')
		j++;
	line = ft_calloc((j + 1), sizeof(char));
	if (!line)
		return (NULL);
	k = ft_strlen(keeper) - j;
	while (i < j)
		line[i++] = *keeper++;
	storage = ft_memcpy(storage, keeper, k);
	storage[k] = '\0';
	return (line);
}

/*1.copies our read amount into new "keeper" line
  2. frees the previous "keeper" line
  3. at the end we get result of "old keeper line" + read amount*/
char	*strjoin_free(char *s1, const char *s2)
{
	char	*res;

	if (!s2)
		return (free(s1), NULL);
	res = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!res)
		return (free(s1), NULL);
	ft_memcpy(res, s1, ft_strlen(s1));
	ft_memcpy(res + ft_strlen(s1), s2, ft_strlen(s2));
	res[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	free(s1);
	return (res);
}

/*1. duplicates what was left from previous iteration into "keeper" line.
  2. reads next amount from the file till we find \n inside.
  3. attaches what was read to our "keeper" line.*/
char	*dup_read_join(int fd, char *storage, char *reader)
{
	char	*keeper2;
	int		bytes_read;

	if (storage)
		keeper2 = ft_strdup(storage);
	else
		keeper2 = ft_strdup("");
	if (!keeper2)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strrchr(keeper2, '\n'))
	{
		bytes_read = read(fd, reader, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(keeper2), NULL);
		reader[bytes_read] = '\0';
		keeper2 = strjoin_free(keeper2, reader);
		if (!keeper2)
			return (NULL);
	}
	return (keeper2);
}

char	*get_next_line(int fd)
{
	static char	storage[BUFFER_SIZE];
	char		*reader;
	char		*keeper;
	char		*final_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reader = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!reader)
		return (NULL);
	keeper = dup_read_join(fd, storage, reader);
	final_line = extract_save(keeper, storage);
	free(reader);
	free(keeper);
	if (final_line == NULL || *final_line != 0)
		return (final_line);
	free(final_line);
	return (NULL);
}

int	main(void)
{
	int		fd;
	int		count;
	char	*nxln;

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
