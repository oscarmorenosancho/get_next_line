/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:51:04 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/27 19:43:09 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define SS_E_NORMAL		0
# define SS_E_FREE_SRC		1
# define STR_S_NORMAL		0
# define STR_S_MALLOC		1
# define STR_S_SET0END		2
# define STR_S_FREE			4
# define SJ_E_NORMAL		0
# define SJ_E_FR_S1			1
# define SJ_E_FR_S2			2

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_strsave
{
	char	*pd;
	char	*ps;
	char	*pe;
}	t_strsave;

typedef struct s_strjoin_ext
{
	size_t	s1_len;	
	size_t	s2_len;
	size_t	tot_len;
	char	*buf;
}	t_strjoin_ext;

typedef struct s_substr_ext
{
	char	*p;
	char	*ss;
	size_t	s_len;
	size_t	ss_len;
}	t_substr_ext;

typedef struct s_ext_l_from_buf
{
	char	*p;
	char	*line;
	size_t	line_size;
}	t_ext_l_from_buf;

typedef struct s_read_next_l
{
	char	*nw_chk;
	int		j_err;
}	t_read_next_l;

typedef struct s_get_next_l
{
	char	*buf;
	char	*line;
	int		r_r;
}	t_get_next_l;

size_t	ft_strlen(const char *s);
char	*ft_strsave(char *dst, char **src, size_t n, int mode);
int		ft_strjn_x(char **dest, char **s1, char **s2, int mode);
char	*ft_substr_ext(char **s, unsigned int start,
			size_t len, int mode);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);

#endif