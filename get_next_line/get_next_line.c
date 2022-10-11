/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:22:42 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/11 18:57:18 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	ft_get_next_chunk(int fd, size_t size, char **chunk)
{
	int		read_ret;

	read_ret = -1000;
	*chunk = (char *)malloc(size + 1);
	if (! *chunk)
		return (read_ret);
	read_ret = read(fd, *chunk, size);
	if (read_ret <= 0)
	{
		free(*chunk);
		*chunk = NULL;
	}
	else
		(*chunk)[read_ret] = 0;
	return (read_ret);
}

char	*ft_append_chunk_to_buf(int fd, char **buffer, int *read_ret)
{
	char	*new_buf;
	char	*new_chunk;

	*read_ret = ft_get_next_chunk(fd, BUFFER_SIZE, &new_chunk);
	if (! *buffer)
		*buffer = new_chunk;
	else if (new_chunk)
	{
		new_buf = ft_strjoin(*buffer, new_chunk);
		free (new_chunk);
		free (*buffer);
		*buffer = new_buf;
	}
	return (*buffer);
}

char	*ft_extract_line_from_buf(char **buffer, size_t	buf_size)
{
	char	*p;
	char	*line;
	size_t	line_size;

	if (! *buffer)
		return (NULL);
	p = ft_strchr(*buffer, '\n');
	if (! p)
		return (NULL);
	line_size = p - *buffer + 1;
	line = ft_substr_empty2null(*buffer, 0, line_size, 1);
	if (!line)
		return (NULL);
	p = ft_substr_empty2null(*buffer, line_size, buf_size, 0);
	if (p)
	{
		if (*buffer)
			free(*buffer);
		*buffer = p;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	int			read_ret;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	read_ret = 1;
	line = NULL;
	while ((read_ret > 0) && !line)
	{
		if (ft_append_chunk_to_buf(fd, &buffer, &read_ret) && read_ret >= 0)
			line = ft_extract_line_from_buf(&buffer, ft_strlen(buffer));
		if (!line && buffer && read_ret == 0)
		{
			line = buffer;
			buffer = NULL;
		}
	}
	if (line && (read_ret < 0 || !line[0]))
	{
		free (line);
		line = NULL;
	}
	return (line);
}

int	main(int argc, char const *argv[])
{
	int		fd;
	int		close_res;
	char	*filename;
	char	*line;
	int		i;

	fd = 0;
	if (argc == 2)
	{
		filename = (char *)argv[1];
		fd = open(filename, O_RDONLY);
		printf("main: using file:\n%s\n", filename);
	}
	else
		printf("main: using stdin:\n");
	if (fd < 0)
		return (0);
	i = 0;
	printf("\n--main: line %d search\n", i);
	line = get_next_line(fd);
	while (line)
	{
		printf("main: get_next_line:\n%s\n", line);
		if (line)
		{
			free(line);
			line = NULL;
		}
		i++;
		printf("main: loop %d\n", i);
		line = get_next_line(fd);
	}
	close_res = close(fd);
	if (! close_res)
		printf("close failed");
	return (0);
}
