/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:49:28 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/23 10:42:44 by omoreno-         ###   ########.fr       */
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

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*pd;
	char	*ps;
	char	*pe;

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
