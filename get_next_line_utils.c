/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gperedny <gperedny@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/04 12:41:31 by gperedny          #+#    #+#             */
/*   Updated: 2025/06/12 14:47:03 by gperedny         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	int i;
	char *dest;

	i = 0;
	while (s[i] != '\0')
		i++;
	dest = (char *)malloc((i + 1) * sizeof(char));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*str;
	unsigned char	*c;
	size_t n;

	if (nmemb == 0 || size == 0)
	{
		return (malloc(1));
	}
	if ((SIZE_MAX / size) < nmemb)
		return (NULL);
	str = malloc(nmemb * size);
	if (!str)
		return (NULL);
	c = str;
	n = nmemb * size;
	while (n > 0)
	{
		*c = 0;
		c++;
		n--;
	}
	return (str);
	//return (ft_bzero(str, nmemb * size));
}