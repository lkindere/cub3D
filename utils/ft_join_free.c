/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkindere <lkindere@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/24 06:10:58 by lkindere          #+#    #+#             */
/*   Updated: 2022/06/12 17:49:01 by lkindere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static size_t	ft_strlena(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_join_free(char const *s1, char const *s2, int sfree)
{
	char	*join;
	int		s1_len;
	int		s2_len;
	int		i;

	s1_len = ft_strlena(s1);
	s2_len = ft_strlena(s2);
	i = 0;
	join = malloc(s1_len + s2_len + 1);
	if (!join)
		return (NULL);
	while (s1 && s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2 && s2[i])
		join[s1_len++] = s2[i++];
	join[s1_len] = '\0';
	if ((sfree == 1 || sfree == 3) && s1)
		free((void *)s1);
	if ((sfree == 2 || sfree == 3) && s2)
		free((void *)s2);
	return (join);
}
