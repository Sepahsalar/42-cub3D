/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 15:50:55 by asohrabi          #+#    #+#             */
/*   Updated: 2024/08/26 17:28:34 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3D.h"

static void	check_open_failure(t_all *all, int fd)
{
	if (fd == -1)
		terminate(all, "Opening map file failed", NULL, NULL);
}

void	check_read_failure(t_all *all, int byte, int flag)
{
	if (byte == -1)
		terminate(all, "Reading from file failed", NULL, NULL);
	if (!flag && !byte)
		terminate(all, "Empty file", NULL, NULL);
}

void	reader(t_all *all)
{
	char	c[2];
	int		byte;
	char	*temp;
	int		fd;

	c[1] = '\0';
	all->strmap = NULL;
	fd = open(all->argv, O_RDONLY);
	check_open_failure(all, fd);
	byte = read(fd, c, 1);
	check_read_failure(all, byte, 0);
	while (byte)
	{
		temp = all->strmap;
		all->strmap = ft_strjoin(all->strmap, c);
		free(temp);
		if (!all->strmap)
			terminate(all, "Joining strings failed", NULL, NULL);
		byte = read(fd, c, 1);
		check_read_failure(all, byte, 1);
	}
	if (close(fd) == -1)
		terminate(all, "Closing file failed", NULL, NULL);
}

char	*custom_strnstr(char *haystack, char *needle)
{
	char	*temp;

	temp = ft_strnstr(haystack, needle, ft_strlen(haystack));
	while (temp)
	{
		if (temp[ft_strlen(needle)] == ' ')
			return (temp);
		temp = ft_strnstr(temp + 1, needle, ft_strlen(haystack));
	}
	return (NULL);
}

char	*finder(t_all *all, char *str)
{
	char	*found;

	found = custom_strnstr(all->strmap, str);
	if (found)
		return (custom_strdup(all, found, str));
	terminate(all, "There is no ", str, " identifier in the map");
	return (NULL);
}
