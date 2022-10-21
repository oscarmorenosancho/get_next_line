/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:51:04 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/17 16:13:14 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_chunk_node
{
	char			*content;
	char			*line_sep;
	size_t			cont_size;
	t_chunk_node	*next;
}	t_chunk_node;

typedef struct s_buffer_info
{
	int				fd;
	char			*buffer;
	char			*chunk;
	t_chunk_node	*chunk_list;
	t_chunk_node	*chunk_last;
	char			*line;
	size_t			read_res;
	size_t			mem_size;
	size_t			buffer_size;
	size_t			chunk_size;
	size_t			total_read;
	size_t			line_size;
}	t_buffer_info;

size_t	ft_strlen(const char *s);
void	*ft_memcpy(void *dst, const void *src, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr_empty2null(char const *s, unsigned int start, size_t len,
			int empty2null);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);

#endif