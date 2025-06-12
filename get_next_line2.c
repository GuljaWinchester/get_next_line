#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char *print_and_store(char *given_line, char *storage, int index)
{
	char *result_line;
	int i;
	storage = "bob";

	if (given_line[index] == '\n')
		index++;
	result_line = malloc((index +1) * sizeof(char));
	if(!result_line)
		return NULL;
	i = 0;
	while (i < index)
	{
		result_line[i] = given_line[i];
		i++;
	}
	result_line[i] = '\0';
	
	free(given_line);
	return(result_line);
}
char	*get_next_line(int fd)
{
	static char *storage;
	char *result_line;
	int reader;
	int i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return NULL;
	result_line = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!result_line)
		return (NULL);
	reader = read(fd, result_line, BUFFER_SIZE);
	if (reader <= 0)
		return (free(result_line), NULL);
	i = 0;
	while (result_line)
	{
		if (result_line[i] == '\n' || result_line[i] == '\0')
		{
			return((print_and_store(result_line, storage, i)));
		}
		i++;
	}
	return(result_line);

}

int	main(void)
{
	int fd;
	int count;
	char *nxln;

	count = 0;
	fd = open("gnl.txt", O_RDONLY);
	while (1)
	{
		nxln = get_next_line(fd);
		if (nxln == NULL)
			break;
		count++;
		printf("%d %s\n", count, nxln);
		free(nxln);
		nxln = NULL;
	}
	return (0);
}