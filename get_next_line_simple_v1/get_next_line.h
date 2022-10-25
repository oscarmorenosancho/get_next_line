/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:51:04 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/25 18:25:01 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_ext_l_from_buf
{
	char	*p;
	char	*line;
	size_t	line_size;
}	t_ext_l_from_buf;

typedef struct s_get_next_l
{
	char	*buffer;
	char	*line;
	int		r_r;
}	t_get_next_l;

size_t	ft_strlen(const char *s);
char	*ft_strsave(char *dst, const char *src, size_t n, int mode);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr_empty2null(char const *s, unsigned int start,	size_t len,
			int empty2null);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);

#endif