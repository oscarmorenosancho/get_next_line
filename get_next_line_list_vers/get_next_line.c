/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:22:42 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/21 18:42:56 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#define MIN_CHUNK_SIZE 42
#define FAIL_MEM_ALLOC_READ_RET	-1000

int	ft_read_chunk(int fd, t_chunk_node *c_n, size_t buf_size)
{
	c_n->content = (char *)malloc(buf_size + 1);
	if (! c_n->content)
		return (FAIL_MEM_ALLOC_READ_RET);
	c_n->cont_size = read(fd, c_n->content, buf_size);
	if (c_n->cont_size <= 0)
	{
		free(c_n->content);
		c_n->content = NULL;
	}
	else
		(c_n->content)[c_n->cont_size] = 0;

	return (c_n->cont_size);
}

int	ft_push_next_chunk(t_buffer_info *b_i)
{
	t_chunk_node	*c_n;

	c_n = (t_chunk_node *)malloc (sizeof(t_chunk_node));
	if (!c_n)
		return (FAIL_MEM_ALLOC_READ_RET);
	c_n->next = NULL;
	b_i->read_res = ft_read_chunk(b_i->fd, c_n, b_i->chunk_size);
	if (c_n->cont_size > 0)
	{
		c_n->line_sep = ft_strchr(c_n->content, '\n');
		if (b_i->chunk_list && b_i->chunk_last)
			b_i->chunk_last->next = c_n;
		else
			b_i->chunk_list = c_n;
		b_i->chunk_last = c_n;
		if (c_n->line_sep)
			b_i->line_size += (c_n->line_sep - c_n->content + 1);
		else
			b_i->line_size += c_n->cont_size;
	}
	else
		free (c_n);
	return (b_i->read_res);
}

int	ft_pop_next_line(t_buffer_info *b_i)
{
	char			*p;
	t_chunk_node	*c_n;
	size_t			remained;	

	if (b_i->line_size > 0 && b_i->chunk_list)
	{
		b_i->line = (char *)malloc(b_i->line_size + 1);
		if (! b_i->line)
			return (FAIL_MEM_ALLOC_READ_RET);
		p = b_i->line;
		c_n = b_i->chunk_list;
		while (c_n && c_n->content)
		{
			if (!c_n->line_sep)
			{
				ft_memcpy(p, c_n->content, c_n->cont_size);
				p[c_n->cont_size] = 0;
				p += c_n->cont_size;
			}
			else
			{
				remained = c_n->cont_size - (c_n->line_sep - c_n->content + 1);
				ft_memcpy(p, c_n->content, c_n->line_sep - c_n->content + 1);
				if (remained > 0)
				{
					ft_memcpy(c_n->content, c_n->line_sep + 1, remained);
				}
				
				return (b_i->line);
			}
			c_n = c_n->next;
			//TODO: clean chunk node alredy poped
		}
		return (b_i->line);
	}
	else if (b_i->line_size > 0)
		b_i->line_size = 0;
	return (NULL);
}

int	ft_clear_chunk_list(t_chunk_node **list_n)
{
	t_chunk_node	*n_n;

	if (*list_n && (*list_n)->next)
		return (ft_clear_chunk_list(&((*list_n)->next)));
	if (*list_n)
		free (*list_n);
	*list_n = NULL;
	return (0);
}

char	*get_next_line(int fd)
{
	static t_buffer_info	b_i;

	b_i.buffer_size = BUFFER_SIZE;
	b_i.buffer_size = MIN_CHUNK_SIZE;
	if (fd < 0 || b_i.buffer_size < 1)
		return (NULL);
	b_i.fd = fd;
	b_i.read_res = 1;
	b_i.line_size = 0;
	b_i.line = NULL;
	while (ft_push_next_chunk(&b_i) > 0 && ! b_i.chunk_last)
		;
	if (b_i.read_res >= 0)
		b_i.line = ft_pop_next_line(&b_i);
	else
	{
		ft_clear_chunk_list(&(b_i.chunk_list));
		b_i.chunk_last = NULL;
		return (NULL);
	}
	return (b_i.line);
}

/*int	ft_get_next_chunk(t_buffer_info *b_i)
{
	b_i->read_res = 1;
	b_i->total_read = 0;
	if (b_i->buffer_size > b_i->chunk_size)
		b_i->chunk_size = b_i->buffer_size;
	b_i->chunk = (char *)malloc(b_i->chunk_size + 1);
	if (! b_i->chunk)
		return (FAIL_MEM_ALLOC_READ_RET);
	while (b_i->read_res > 0 &&
		(b_i->chunk_size - b_i->total_read) >= b_i->buffer_size)
	{
		b_i->read_res = read(b_i->fd, b_i->chunk + b_i->total_read,
				b_i->buffer_size);
		if (b_i->read_res > 0)
			b_i->total_read += b_i->read_res;
		if (b_i->read_res < 0 || b_i->total_read == 0)
		{
			free(b_i->chunk);
			b_i->chunk = NULL;
			b_i->total_read = b_i->read_res;
		}
		else
			(b_i->chunk)[b_i->total_read] = 0;
	}
	return (b_i->total_read);
}

char	*ft_append_chunk_to_buf(t_buffer_info *b_i)
{
	char	*new_buf;

	ft_get_next_chunk(b_i);
	if (! b_i->buffer && ! b_i->chunk)
		return (NULL);
	if (b_i->chunk)
	{
		if (b_i->buffer)
		{
			new_buf = ft_strjoin(b_i->buffer, b_i->chunk);
			free (b_i->buffer);
			b_i->buffer = NULL;
		}
		else
			new_buf = ft_strjoin("", b_i->chunk);
		free (b_i->chunk);
		b_i->chunk = NULL;
		b_i->buffer = new_buf;
	}
	return (b_i->buffer);
}

char	*ft_extract_line_from_buf(t_buffer_info *b_i)
{
	char	*p;

	if (! b_i->buffer)
		return (NULL);
	p = ft_strchr(b_i->buffer, '\n');
	if (! p)
		return (NULL);
	b_i->line_size = p - b_i->buffer + 1;
	b_i->line = ft_substr_empty2null(b_i->buffer, 0, b_i->line_size, 1);
	if (! b_i->line)
		return (NULL);
	p = ft_substr_empty2null(b_i->buffer, b_i->line_size, b_i->buffer_size, 0);
	if (p)
	{
		if (b_i->buffer)
			free(b_i->buffer);
		b_i->buffer = p;
	}
	return (b_i->line);
}

char	*get_next_line(int fd)
{
	static t_buffer_info	b_i;

	b_i.buffer_size = BUFFER_SIZE;
	b_i.buffer_size = MIN_CHUNK_SIZE;
	if (fd < 0 || b_i.buffer_size < 1)
		return (NULL);
	b_i.fd = fd;
	b_i.read_res = 1;
	b_i.line = NULL;
	while ((b_i.read_res > 0) && ! b_i.line)
	{
		if (ft_append_chunk_to_buf(&b_i) && b_i.read_res >= 0)
			b_i.line = ft_extract_line_from_buf(&b_i);
		if (!b_i.line && b_i.buffer && b_i.read_res == 0)
		{
			b_i.line = b_i.buffer;
			b_i.buffer = NULL;
		}
	}
	if (b_i.line && (b_i.read_res < 0 || !b_i.line[0]))
	{
		free (b_i.line);
		b_i.line = NULL;
	}
	return (b_i.line);
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
}*/
