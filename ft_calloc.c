/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansimonn <ansimonn@student.42angouleme.f>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 10:43:59 by ansimonn          #+#    #+#             */
/*   Updated: 2026/03/12 15:47:23 by ansimonn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;
	size_t	i;

	if (size != 0 && nmemb * size / size != nmemb)
		return (NULL);
	res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		((char *)res)[i] = 0;
		++i;
	}
	return (res);
}
