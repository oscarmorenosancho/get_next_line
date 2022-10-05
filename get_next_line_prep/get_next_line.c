/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:22:42 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/05 16:23:35 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#define SIZE_OF_CHUNK 50

void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_realloc(void *src, size_t n, size_t n_inc);

static char	*ft_reset_reading(char **buf, size_t *buf_size, size_t *cur_used)
{
	if (*buf)
		free(*buf);
	*buf = NULL;
	*cur_used = 0;
	*buf_size = 0;
	return (*buf);
}

static char	*ft_adapt_buf_size(char **buf, size_t *buf_size, size_t *cur_used)
{
	static char		*realloc_buf;

	if (*cur_used >= *buf_size)
	{
		realloc_buf = ft_realloc(*buf, *buf_size, SIZE_OF_CHUNK);
		if (! realloc_buf)
			return (ft_reset_reading(buf, buf_size, cur_used));
		*buf_size += SIZE_OF_CHUNK;
		*buf = realloc_buf;
	}
	return (*buf);
}

char	*get_next_line(int fd)
{
	static char		*buf;
	static size_t	i;
	static size_t	buf_size;
	size_t			read_count;

	if (buf && i > 0 && buf[i] == '\n')
		ft_reset_reading(&buf, &buf_size, &i);
	if (! ft_adapt_buf_size(&buf, &buf_size, &i))
		return (NULL);
	read_count = 1;
	while (read_count > 0 && (i == 0 || buf[i] != '\n'))
	{
		if (! ft_adapt_buf_size(&buf, &buf_size, &i))
			return (NULL);
		read_count = read(fd, buf + i, 1);
		if (read_count < 0)
			return (NULL);
		i++;
	}
	if (buf[i] == '\n')
		return (buf);
	return (NULL);
}
