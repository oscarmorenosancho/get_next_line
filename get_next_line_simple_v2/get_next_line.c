/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:22:42 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/26 19:08:53 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#define MIN_CHUNK_SIZE 80
#define FAIL_MEM_ALLOC_READ_RET	-1000

int	ft_get_next_chunk(int fd, char **chunk, \
	size_t	chunk_size, size_t	buffer_size)
{
	int		read_ret;
	size_t	total_read;

	read_ret = 1;
	total_read = 0;
	if (buffer_size > chunk_size)
		chunk_size = buffer_size;
	*chunk = (char *)malloc(chunk_size + 1);
	if (! *chunk)
		return (FAIL_MEM_ALLOC_READ_RET);
	while (read_ret > 0 && (chunk_size - total_read) >= buffer_size)
	{
		read_ret = read(fd, *chunk + total_read, buffer_size);
		if (read_ret > 0)
			total_read += read_ret;
		if (read_ret < 0 || total_read == 0)
		{
			free(*chunk);
			*chunk = NULL;
			total_read = read_ret;
		}
		else
			(*chunk)[total_read] = 0;
	}
	return (total_read);
}

char	*ft_extract_line_from_buf(t_get_next_l *gnls)
{
	t_ext_l_from_buf	s;

	if (! gnls->buffer)
		return (NULL);
	s.p = ft_strchr(gnls->buffer, '\n');
	if (! s.p)
		return (NULL);
	s.line_size = s.p - gnls->buffer + 1;
	s.line = ft_substr_ext(&(gnls->buffer), 0, s.line_size, SS_E_AVOID_EMPTY);
	if (!s.line)
		return (NULL);
	s.p = ft_substr_ext(&(gnls->buffer), s.line_size, \
		ft_strlen(gnls->buffer), SS_E_NORMAL);
	if (s.p)
	{
		if (gnls->buffer)
			free(gnls->buffer);
		gnls->buffer = s.p;
	}
	return (s.line);
}

char	*ft_read_next_line(int fd, t_get_next_l *gnls)
{
	char	*new_chunk;

	gnls->r_r = ft_get_next_chunk(fd, &new_chunk, MIN_CHUNK_SIZE, BUFFER_SIZE);
	if (! gnls->buffer && ! new_chunk)
		return (NULL);
	if (new_chunk)
	{
		gnls->buffer = ft_strjoin_ext(&(gnls->buffer), &new_chunk, \
			SJ_E_FREE_S1);
		if (new_chunk)
			free (new_chunk);
	}
	if (gnls->buffer && gnls->r_r >= 0)
			gnls->line = ft_extract_line_from_buf(gnls);
	if (! gnls->line && gnls->buffer && gnls->r_r == 0)
	{
		gnls->line = gnls->buffer;
		gnls->buffer = NULL;
	}
	return (gnls->line);
}

char	*get_next_line(int fd)
{
	static t_get_next_l	s;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	s.r_r = read(fd, NULL, 0);
	s.r_r = s.r_r >= 0;
	s.line = NULL;
	while ((s.r_r > 0) && ! s.line)
		s.line = ft_read_next_line(fd, &s);
	if (s.line && (s.r_r < 0 || ! s.line[0]))
	{
		free (s.line);
		s.line = NULL;
	}
	if (s.buffer && (s.r_r < 0 || ! s.line))
	{
		free (s.buffer);
		s.buffer = NULL;
	}
	return (s.line);
}

/*int	main(void)
{
	char s1[] = "012345678909123456789";
	char s2[] = "abcdefghijklmnopqrstu";

	ft_strsave(s2, s1, 10, STR_S_SET0END);
	write(1, s2, 21);
	return (0);
}*/

/*int	main(int argc, char const *argv[])
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
		printf("main: get_next_line:\n(sl)%s(el)\n", line);
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
}*/
