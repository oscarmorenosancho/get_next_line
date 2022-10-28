/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:49:28 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/28 17:33:13 by omoreno-         ###   ########.fr       */
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

char	*ft_strsave(char *dst, char **src, size_t n, int mode)
{
	t_strsave	st;

	if (! src)
		return (NULL);
	if (! dst && (mode & STR_S_MALLOC))
		dst = (char *)malloc(n + 1);
	if (! dst && (mode & STR_S_MALLOC))
		return (NULL);
	if (dst != *src)
	{
		st.pd = dst;
		st.ps = *src;
		st.pe = st.ps + n;
		while (st.ps < st.pe)
			*(st.pd++) = *(st.ps++);
		if (mode & STR_S_SET0END)
			*(st.pd) = 0;
		if ((mode & STR_S_FREE) && src && *src)
			free_x((void **)src);
	}
	return (dst);
}

int	ft_strjn_x(char **dest, char **s1, char **s2, int mode)
{
	t_strjoin_ext	st;

	st.s1_len = 0;
	st.s2_len = 0;
	if (s1 && *s1)
		st.s1_len = ft_strlen(*s1);
	if (s2 && *s2)
		st.s2_len = ft_strlen(*s2);
	st.tot_len = st.s1_len + st.s2_len;
	st.buf = (char *)malloc(st.tot_len + 1);
	if (!st.buf)
	{
		if (dest)
			*dest = NULL;
		return (1);
	}
	if (s1 && *s1)
		ft_strsave(st.buf, s1, st.s1_len, \
			STR_S_SET0END + STR_S_FREE * (mode & SJ_E_FR_S1));
	if (s2 && *s2)
		ft_strsave(st.buf + st.s1_len, s2, st.s2_len, \
			STR_S_SET0END + STR_S_FREE * (mode & SJ_E_FR_S2));
	if (dest)
		*dest = st.buf;
	return (0);
}

char	*ft_substr_ext(char **s, unsigned int start,
	size_t len, int mode)
{
	t_substr_ext	st;

	st.s_len = ft_strlen(*s);
	st.p = *s + start;
	st.ss_len = st.s_len - start;
	if (st.ss_len > len)
		st.ss_len = len;
	if (start >= st.s_len)
	{
		st.p = (char *)s + st.s_len;
		st.ss_len = 0;
	}
	st.ss = NULL;
	st.ss = ft_strsave(st.ss, &(st.p), st.ss_len, \
		STR_S_SET0END + STR_S_MALLOC);
	if ((mode & SS_E_FREE_SRC) && s && *s)
		free_x((void **)s);
	return (st.ss);
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
