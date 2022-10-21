/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:49:28 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/17 16:14:22 by omoreno-         ###   ########.fr       */
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

char	*ft_strjoin(char const *s1, char const *s2)
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
}

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
