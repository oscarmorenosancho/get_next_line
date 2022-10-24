/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:51:04 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/24 18:37:04 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define FAIL_MEM_ALLOC_READ_RET	-1000
# define MIN_CHUNK_SIZE 50

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_chunk_node
{
	char				*content;
	char				*line_sep;
	long int			cont_size;
	struct s_chunk_node	*next;
}	t_chunk_node;

typedef struct s_buffer_info
{
	int				fd;
	t_chunk_node	*chunk_list;
	t_chunk_node	*chunk_last;
	char			*line;
	char			*line_end;
	long int		read_res;
	size_t			buffer_size;
	size_t			line_size;
}	t_buffer_info;

size_t			ft_strlen(const char *s);
char			*ft_strsave(char *dst, const char *src, size_t n);
char			*ft_strchr(const char *s, int c);
char			*get_next_line(int fd);
t_chunk_node	*ft_clear_list_til_node(t_chunk_node **list_n,
					t_chunk_node *to_keep);
int				ft_read_chunk(t_buffer_info *b_i, \
					t_chunk_node *c_n, size_t chunk_size);

#endif