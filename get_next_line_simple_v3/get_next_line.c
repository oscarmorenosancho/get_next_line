/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:22:42 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/27 19:45:23 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

#define MIN_CHUNK_SIZE 1
#define FAIL_MEM_ALLOC_READ_RET	-1000

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
			free (st.nw_chk);
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
	{
		free (s.line);
		s.line = NULL;
	}
	if (s.buf && (s.r_r < 0 || ! s.line))
	{
		free (s.buf);
		s.buf = NULL;
	}
	return (s.line);
}

/*int	main(void)
{
	char	*s1 = "01234567890123456789";
	char	*s2 = "abcdefghijklmnopqrst";
	char	*ps1;
	char	*ps2;
	char	*pjoin;

	printf ("input pointers %p %p, %s %s\n", s1, s2, s1, s2);
	printf ("--------\n");
	ps1 = ft_strsave(NULL, &s1, 30, STR_S_MALLOC + STR_S_SET0END);
	ps2 = ft_strsave(NULL, &s2, 30, STR_S_MALLOC + STR_S_SET0END);
	printf ("out pointers %p %p, %s %s\n", ps1, ps2, ps1, ps2);
	printf ("--------\n");
	pjoin = ft_strjoin_ext(&ps1, &ps2, 0);
	printf ("join input pointers %p %p, %s %s\n", ps1, ps2, ps1, ps2);
	printf ("join output pointe %p , %s\n", pjoin, pjoin);
	if (ps1)
	{
		free(ps1);
		ps1 = NULL;
	}
	if (ps2)
	{
		free(ps2);
		ps2 = NULL;
	}
	if (pjoin)
	{
		free(pjoin);
		pjoin = NULL;
	}
	printf ("out pointers %p %p %p, %s %s %s\n", ps1, ps2, pjoin, ps1, ps2, pjoin);
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
