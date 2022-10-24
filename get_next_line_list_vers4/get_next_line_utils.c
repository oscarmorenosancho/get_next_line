/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:49:28 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/24 18:37:36 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strsave(char *dst, const char *src, size_t n)
{
	char	*pd;
	char	*ps;
	char	*pe;

	if (! dst)
		dst = (char *)malloc(n + 1);
	if (! dst)
		return (NULL);
	if (dst != src)
	{
		pd = (char *)dst;
		ps = (char *)src;
		pe = ps + n;
		while (ps < pe)
		{
			*pd = *ps;
			pd++;
			ps++;
		}
		*pe = 0;
	}
	return (dst);
}

char	*ft_strchr(const char *s, int c)
{
	char	*p;

	p = (char *)s;
	while (*p && *p != (char)c)
		p++;
	if (*p != (char)c)
		return (NULL);
	return (p);
}

t_chunk_node	*ft_clear_list_til_node(t_chunk_node **list_n,
	t_chunk_node *to_keep)
{
	if (! list_n || ! *list_n)
		return (NULL);
	if (*list_n != to_keep)
	{
		if ((*list_n)->next && (*list_n)->next != to_keep)
			ft_clear_list_til_node(&((*list_n)->next), to_keep);
		if ((*list_n)->content)
			free ((*list_n)->content);
		free (*list_n);
		*list_n = to_keep;
	}
	return (*list_n);
}

int	ft_read_chunk(t_buffer_info *b_i, t_chunk_node *c_n, size_t chunk_size)
{
	int		read_res;

	printf("\n\t\t\tft_read_chunk at start:\n");
	read_res = 1;
	c_n->cont_size = 0;
	if (b_i->buffer_size > chunk_size)
		chunk_size = b_i->buffer_size;
	printf("\n\t\t\tft_read_chunk before malloc:\n");
	c_n->content = (char *)malloc(chunk_size + 1);
	printf("\n\t\t\tft_read_chunk after malloc:\n");
	if (! c_n->content)
		return (FAIL_MEM_ALLOC_READ_RET);
	while (read_res > 0 && (chunk_size - c_n->cont_size) >= b_i->buffer_size)
	{
		printf("\n\t\t\tft_read_chunk before read:\n");
		read_res = read(b_i->fd, \
			c_n->content + c_n->cont_size, b_i->buffer_size);
		if (read_res > 0)
			c_n->cont_size += read_res;
		if (read_res < 0 || c_n->cont_size == 0)
		{
			printf("\n\t\t\tft_read_chunk before free:\n");
			free(c_n->content);
			printf("\n\t\t\tft_read_chunk after free:\n");
			c_n->content = NULL;
			c_n->cont_size = read_res;
		}
		else
			(c_n->content)[c_n->cont_size] = 0;
	}
	printf("\n\t\t\tft_read_chunk before return:\n");
	return (c_n->cont_size);
}
