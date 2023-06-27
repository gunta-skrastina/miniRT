/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:54:46 by fjerinic          #+#    #+#             */
/*   Updated: 2023/06/27 13:45:31 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	parse_error(t_scene *scene, int fd)
{
	close(fd);
	error_v2(scene);
}

int	print_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (-1);
}

void	fatal_error(char *str)
{
	perror(str);
	exit(0);
}

void	error_v2(t_scene *scene)
{
	if (scene != NULL)
		ft_putstr_fd("map error", 2);
	//free_scene(scene);
	exit(0);
}

void	check_dub(double num, t_scene *scene, int flag)
{
	if (flag == 0)
		return ;
	else if (flag == 1 && (num < 0 || num > 1))
		error_v2(scene);
	else if (flag == 2 && (num < 0 || num > 180))
		error_v2(scene);
	else if (flag == 3 && (num < 1 || num > 10))
		error_v2(scene);
}
