/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:22:42 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/10 12:49:11 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*ft_get_next_chunk(int fd, size_t size, int *eof_flag, int *err_flag )
{
	char	*chunk;
	size_t	read_ret;

	*eof_flag = 0;
	*err_flag = 1;
	chunk = (char *)malloc(size + 1);
	if (! chunk)
		return (NULL);
	read_ret = read(fd, chunk, size);
	*eof_flag = (read_ret < size);
	*err_flag = read_ret < 0;
	if (read_ret <= 0)
	{
		free(chunk);
		chunk = NULL;
	}
	else
		chunk[read_ret] = 0;
	return (chunk);
}

char	*ft_append_chunk_to_buf(char **buffer, char **chunk)
{
	char	*new_buf;

	if (! *buffer)
		*buffer = *chunk;
	else if (*chunk)
	{
		new_buf = ft_strjoin(*buffer, *chunk);
		if (! new_buf)
			return (NULL);
		free (*buffer);
		if (*chunk)
			free (*chunk);
		*buffer = new_buf;
	}
	return (*buffer);
}

char	*ft_extract_line_from_buf(char **buffer)
{
	char	*p;
	char	*line;
	size_t	line_size;
	size_t	buf_size;

	buf_size = ft_strlen(*buffer);
	p = ft_strchr(*buffer, '\n');
	if (! p)
		return (NULL);
	line = ft_substr(*buffer, 0, p - *buffer + 1);
	if (!line)
		return (NULL);
	p++;
	line_size = p - *buffer;
	p = ft_substr(*buffer, line_size, buf_size);
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
	char		*new_chunk;
	char		*line;
	int			eof_flag;
	int			err_flag;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	eof_flag = 0;
	while (! eof_flag)
	{
		new_chunk = ft_get_next_chunk(fd, BUFFER_SIZE, &eof_flag, &err_flag);
		if (err_flag)
			return (NULL);
		if (new_chunk)
			ft_append_chunk_to_buf(&buffer, &new_chunk);
		line = NULL;
		if (buffer)
		{
			line = ft_extract_line_from_buf(&buffer);
		}
		if (line)
			return (line);
	}
	line = buffer;
	buffer = NULL;
	return (line);
}

int	main(int argc, char const *argv[])
{
	int		fd;
	int		close_res;
	char	*filename;
	char	*line;
	int		i;

	filename = "test";
	if (argc == 2)
	{
		filename = (char *)argv[1];
		fd = open(filename, O_RDONLY);
	}
	else
		fd = 0;
	if (fd < 0)
		return (0);
	i = 0;
	printf("\n--main: line %d search\n", i);
	line = get_next_line(fd);
	while (line){
		printf("main: get_next_line:\n%s\n", line);
		i++;
		printf("main: loop %d\n", i);
		line = get_next_line(fd);
	}
	close_res = close(fd);
	if (! close_res)
		printf("close failed");
	return (0);
}
