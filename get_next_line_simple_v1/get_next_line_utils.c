/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:49:28 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/25 15:47:59 by omoreno-         ###   ########.fr       */
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

char	*ft_strsave(char *dst, const char *src, size_t n, int mode)
{
	char	*pd;
	char	*ps;
	char	*pe;

	if (! dst && (mode & 1))
		dst = (char *)malloc(n + 1);
	if (! dst && (mode & 1))
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
		if (mode & 2)
			*pe = 0;
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
		ft_strsave(buf, s1, s1_len, 0);
		ft_strsave(buf + s1_len, s2, s2_len + 1, 0);
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
		ft_strsave(ss, p, ss_len, 0);
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
