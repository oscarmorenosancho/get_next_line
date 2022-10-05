/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoreno- <omoreno-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:49:28 by omoreno-          #+#    #+#             */
/*   Updated: 2022/10/05 15:56:49 by omoreno-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

void	*ft_realloc(void *src, size_t n, size_t n_inc)
{
	char	*buf;

	if (n_inc <= 0)
		return (NULL);
	buf = (char *)malloc(n + n_inc);
	if (! buf)
		return (NULL);
	ft_memcpy(buf, src, n);
	free(src);
	return ((void *) buf);
}
