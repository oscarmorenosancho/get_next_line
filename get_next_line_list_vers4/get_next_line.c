/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:22:42 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/24 18:41:41 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

void	ft_print_node_info(t_chunk_node *c_n, const char *tab)
{
	printf("\n\t%sStart Node Data", tab);
	printf("\n\t%sc_n: %p\n", tab, c_n);
	printf("\t%sc_n->content pointer: %p\n", tab, c_n->content);
	if (c_n->content)
		printf("\t%sc_n->content string: (str start)%s(str end)\n", tab, c_n->content);
	printf("\t%sc_n->cont_size: %lu\n", tab, c_n->cont_size);
	printf("\t%sc_n->line_sep pointer: %p\n", tab, c_n->line_sep);
	if (c_n->line_sep)
		printf("\t%sc_n->line_sep string: (str start)%s(str end)\n", tab, c_n->line_sep);
	printf("\t%sc_n->next: %p\n", tab, c_n->next);
	printf("\n\t%sEnd Node Data", tab);
	if (c_n->next)
		ft_print_node_info(c_n->next, tab);
}

void	ft_print_info(t_buffer_info *b_i, const char *tab)
{
	printf("\n%sInfo -----\n", tab);
	printf("%sb_i->fd: %d\n", tab, b_i->fd);
	printf("%sb_i->buffer_size: %lu\n", tab, b_i->buffer_size);
	printf("%sb_i->chunk_last: %p\n", tab, b_i->chunk_last);
	printf("%sb_i->chunk_list: %p\n", tab, b_i->chunk_list);
	printf("%sb_i->line pointer: %p\n", tab, b_i->line);
	if (b_i->line)
		printf("%sb_i->line string: (str start)%s(str end)\n", tab, b_i->line);
	printf("%sb_i->line_end pointer: %p\n", tab, b_i->line_end);
	if (b_i->line_end)
		printf("%sb_i->line_end string: (str start)%s(str end)\n", tab, b_i->line_end);
	printf("%sb_i->line_size: %ld\n", tab, b_i->line_size);
	printf("%sb_i->read_res: %ld\n", tab, b_i->read_res);
	printf("\n%schunk list start -----\n", tab);
	if (b_i->chunk_list)
		ft_print_node_info(b_i->chunk_list, tab);
	printf("\n%schunk list end -----\n", tab);
	printf("%sEnd Info -----\n", tab);
}

int	ft_append_next_chunk(t_buffer_info *b_i)
{
	t_chunk_node	*c_n;

	printf("\n\t\tft_append_next_chunk at start:\n");
	ft_print_info(b_i, "\t\t");
	c_n = (t_chunk_node *)malloc (sizeof(t_chunk_node));
	printf("\n\t\tft_append_next_chunk after malloc:\n");
	if (!c_n)
		return (FAIL_MEM_ALLOC_READ_RET);
	printf("\n\t\tft_append_next_chunk before read:\n");
	c_n->next = NULL;
	b_i->read_res = ft_read_chunk(b_i, c_n, MIN_CHUNK_SIZE);
	printf("\n\t\tft_append_next_chunk after read:\n");
	if (b_i->read_res > 0)
	{
		c_n->line_sep = ft_strchr(c_n->content, '\n');
		printf("\n\t\tft_append_next_chunk after strchr:\n");
		if (b_i->chunk_list && b_i->chunk_last)
			b_i->chunk_last->next = c_n;
		else
			b_i->chunk_list = c_n;
		b_i->chunk_last = c_n;
		if (c_n->line_sep)
			b_i->line_size += (c_n->line_sep - c_n->content + 1);
		else
			b_i->line_size += b_i->read_res;
	}
	else
	{
		printf("\n\t\tft_append_next_chunk before free:\n");
		free (c_n);
	}
	printf("\n\t\tft_append_next_chunk before return:\n");
	ft_print_info(b_i, "\t\t");
	return (b_i->read_res);
}

char	*ft_extract_end_line_from_chunk(t_buffer_info *b_i,
	t_chunk_node *c_n)
{
	size_t			tail_size;

	printf("\n\t\t\tft_extract_end_line_from_chunk at start:\n");
	ft_print_info(b_i, "\t\t\t");
	tail_size = c_n->line_sep - c_n->content + 1;
	c_n->cont_size -= tail_size;
	ft_strsave(b_i->line_end, c_n->content, tail_size);
	b_i->line_end += tail_size;
	if (c_n->cont_size > 0)
	{
		ft_strsave(c_n->content, c_n->line_sep + 1, c_n->cont_size);
		c_n->line_sep = ft_strchr(c_n->content, '\n');
		ft_clear_list_til_node(&(b_i->chunk_list), c_n);
		printf("\n\t\t\tft_extract_end_line_from_chunk before return:\n");
		ft_print_info(b_i, "\t\t\t");
		return (b_i->line);
	}
	ft_clear_list_til_node(&(b_i->chunk_list), NULL);
	printf("\n\t\t\t\tft_extract_end_line_from_chunk before return NO content in c_n:\n");
	ft_print_info(b_i, "\t\t\t");
	return (b_i->line);
}

char	*ft_pop_next_line(t_buffer_info *b_i)
{
	t_chunk_node	*c_n;

	printf("\n\t\tft_pop_next_line at start:\n");
	ft_print_info(b_i, "\t\t");
	if (b_i->line_size > 0 && b_i->chunk_list)
	{
		b_i->line = (char *)malloc(b_i->line_size + 1);
		if (! b_i->line)
			return (NULL);
		b_i->line_end = b_i->line;
		c_n = b_i->chunk_list;
		while (c_n && c_n->content)
		{
			printf("\n\t\tft_pop_next_line at iteration:\n");
			ft_print_info(b_i, "\t\t");
			if (c_n->line_sep)
				return (ft_extract_end_line_from_chunk(b_i, c_n));
			if (c_n->cont_size > 0)
				ft_strsave(b_i->line_end, c_n->content, c_n->cont_size);
			b_i->line_end += c_n->cont_size;
			c_n = c_n->next;
		}
		printf("\n\t\tft_pop_next_line after iterations:\n");
		ft_print_info(b_i, "\t\t");
		ft_clear_list_til_node(&(b_i->chunk_list), NULL);
		b_i->chunk_last = NULL;
		return (b_i->line);
	}
	else if (b_i->line_size > 0)
		b_i->line_size = 0;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_buffer_info	b_i;

	printf("\n\tget_next_line at start:\n");
	ft_print_info(&b_i, "\t");
	if (read(fd, NULL, 0) < 0)
		return (NULL);
	b_i.buffer_size = BUFFER_SIZE;
	if (fd < 0 || b_i.buffer_size < 1)
		return (NULL);
	b_i.fd = fd;
	b_i.line_size = 0;
	b_i.line = 0;
	b_i.line_end = 0;
	if (b_i.chunk_list)
		b_i.line_size = b_i.chunk_list->cont_size;
	b_i.line = NULL;
	while (ft_append_next_chunk(&b_i) > 0
		&& (! b_i.chunk_last || ! b_i.chunk_last->line_sep))
		;
	if (b_i.read_res >= 0)
		b_i.line = ft_pop_next_line(&b_i);
	else
	{
		ft_clear_list_til_node(&(b_i.chunk_list), NULL);
		b_i.chunk_last = NULL;
		return (NULL);
	}
	printf("\nget_next_line before return:\n");
	ft_print_info(&b_i, "\t");
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
		printf("main: get_next_line result:\n(str start)%s(str end)\n", line);
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
