/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnourine <nnourine@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 11:36:16 by nnourine          #+#    #+#             */
/*   Updated: 2024/07/22 14:27:56 by nnourine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>  // For malloc, free, exit
# include <string.h>  // For strerror
# include <unistd.h>  // For open, close, read, write
# include <fcntl.h>   // For file control options
# include <errno.h>   // For errno
# include <stdio.h>   // For printf
# include <math.h>
# include "../lib/libft/libft.h"
# include "../lib/MLX42/include/MLX42/MLX42.h"

# define START_IMAGE_SIZE 100
# define MIN_IMAGE_SIZE 10
# define MAX_MONITOR_USAGE 0.95

typedef struct s_loc
{
	int				x;
	int				y;
	int				z;
	char			c;
	struct s_loc	*next;
	struct s_loc	*previous;
}					t_loc;

typedef struct s_map
{
	char	*north;
	char	*south;
	char 	*west;
	char	*east;
	char	*floor;
	char	*ceil;
	t_loc	*start;
}			t_map;

typedef struct s_all
{
	t_map	*map;
	int		fd;
	char	*strmap;
	char	*argv;
}			t_all;

t_map	*map_parser(t_all *all);
void	terminate(t_all *all, int status);
void	check_failure(int input1, void *input2, int type, t_all *all);
void	reader(t_all *all);

#endif // CUB3D_H