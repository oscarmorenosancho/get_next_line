/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:49:28 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/22 11:26:46 by omoreno-         ###   ########.fr       */
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
	if (*list_n && (*list_n)->next && (*list_n)->next != to_keep)
		ft_clear_chunk_list_til_node(&((*list_n)->next), to_keep);
	if (*list_n && *list_n != to_keep)
	{
		if ((*list_n)->content)
			free ((*list_n)->content);
		free (*list_n);
	}
	*list_n = to_keep;
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

/*char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;	
	size_t	s2_len;
	size_t	tot_len;
	char	*buf;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	tot_len = s1_len + s2_len;
	buf = (char *)malloc(tot_len + 1);
	if (buf)
	{
		ft_memcpy(buf, s1, s1_len);
		ft_memcpy(buf + s1_len, s2, s2_len + 1);
		return (buf);
	}
	return (0);

char	*ft_substr_empty2null(char const *s, unsigned int start,
	size_t len, int empty2null)
{
	char	*p;
	char	*ss;
	size_t	s_len;
	size_t	ss_len;

	s_len = ft_strlen(s);
	p = (char *)s + start;
	ss_len = s_len - start;
	if (ss_len > len)
		ss_len = len;
	if (start >= s_len)
	{
		p = (char *)s + s_len;
		ss_len = 0;
	}
	ss = NULL;
	if (ss_len > 0 || ! empty2null)
		ss = malloc(ss_len + 1);
	if (ss)
	{
		ft_memcpy(ss, p, ss_len);
		ss[ss_len] = 0;
	}
	return (ss);
}
}*/
