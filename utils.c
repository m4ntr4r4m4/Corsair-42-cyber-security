/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahammoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 15:57:53 by ahammoud          #+#    #+#             */
/*   Updated: 2022/07/20 15:58:16 by ahammoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corsair.h"

char	*trim(char *buff)
{
	char	*data;
	char	*tmp;

	tmp = ft_strtrim(buff,"-----BEGIN PUBLIC KEY-----\n");
	data = ft_strtrim(tmp,"-----END\n");
	free(tmp);
	return (data);
}

char	*get_data(char *str)
{
	int		fd;
	char	*buff;
	char	*data;
	int		i;

	fd = open(str, O_RDONLY);
	buff = malloc(sizeof(char) * 2000);
	i = read(fd, buff, 2000);
	if(i < 0)
	{
		free(buff);
		return (NULL);
	}
	buff[i] = '\0';
	data = trim(buff);
	free(buff);
	return (data);
}


