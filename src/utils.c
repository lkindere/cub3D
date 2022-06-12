/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmeising <mmeising@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 02:35:34 by mmeising          #+#    #+#             */
/*   Updated: 2022/06/12 02:36:40 by mmeising         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
 *	Appends char c to the end of string passed by address of itself.
 *	Reallocates and frees the old string.
 *	If str is NULL (no string yet), it creates the str with size 2,
 *	one for char c and one for '\0'.
 */
int	ft_add_char(char **str, char c)
{
	char	*ret;

	if (*str == NULL)
	{
		*str = ft_calloc(2, sizeof(char));
		if (*str == NULL)
			return (1);
		(*str)[0] = c;
	}
	else
	{
		ret = ft_calloc(ft_strlen(*str) + 2, sizeof(char));
		if (ret == NULL)
			return (1);
		ft_strlcpy(ret, *str, ft_strlen(*str) + 1);
		ret[ft_strlen(*str)] = c;
		free(*str);
		*str = ret;
	}
	return (0);
}

/*
 *	Appends string add to the end of string passed by address of itself.
 *	Reallocates and frees the old string.
 *	If str is NULL (no string yet), it creates the str with size of add + 1.
 */
int	ft_add_str(char **str, char *add)
{
	int		i;

	i = -1;
	if (*str == NULL)
	{
		*str = ft_calloc(ft_strlen(add) + 1, sizeof(char));
		if (*str == NULL)
			return (1);
		while (add[++i])
			(*str)[i] = add[i];
	}
	else
	{
		while (add[++i])
			ft_add_char(str, add[i]);
	}
	return (0);
}