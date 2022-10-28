/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:22:42 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/28 17:36:28 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#define MIN_CHUNK_SIZE 1
#define FAIL_MEM_ALLOC_READ_RET	-1000

void	free_x(void **p)
{
	if (p && *p)
	{
		free(*p);
		*p = NULL;
	}
}

int	ft_get_nxt_ck(int fd, char **chunk, \
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
			free_x((void **)chunk);
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

	if (! gnls->buf)
		return (NULL);
	s.p = ft_strchr(gnls->buf, '\n');
	if (! s.p)
		return (NULL);
	s.line_size = s.p - gnls->buf + 1;
	s.line = ft_substr_ext(&(gnls->buf), 0, s.line_size, SS_E_NORMAL);
	if (!s.line)
		return (NULL);
	gnls->buf = ft_substr_ext(&(gnls->buf), s.line_size, \
		ft_strlen(gnls->buf), SS_E_FREE_SRC);
	gnls->line = s.line;
	return (s.line);
}

char	*ft_read_next_line(int fd, t_get_next_l *gnls)
{
	t_read_next_l	st;

	gnls->r_r = ft_get_nxt_ck(fd, &st.nw_chk, MIN_CHUNK_SIZE, BUFFER_SIZE);
	if (gnls->r_r == FAIL_MEM_ALLOC_READ_RET && gnls->buf)
		return (NULL);
	if (! gnls->buf && ! st.nw_chk)
		return (0);
	if (st.nw_chk)
	{
		st.j_err = ft_strjn_x(&(gnls->buf), &(gnls->buf), &st.nw_chk, \
			SJ_E_FR_S1);
		if (st.nw_chk)
			free_x((void **)&st.nw_chk);
		if (st.j_err)
			return (NULL);
	}
	if (!(gnls->buf && gnls->r_r >= 0))
		return (NULL);
	if (! ft_extract_line_from_buf(gnls) && gnls->buf && gnls->r_r == 0)
	{
		gnls->line = gnls->buf;
		gnls->buf = NULL;
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
		free_x ((void **)&s.line);
	if (s.buf && (s.r_r < 0 || ! s.line))
		free_x ((void **)&s.buf);
	return (s.line);
}
