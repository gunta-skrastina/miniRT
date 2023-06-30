/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 15:54:46 by fjerinic          #+#    #+#             */
/*   Updated: 2023/06/29 16:38:42 by gskrasti         ###   ########.fr       */
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
	{
		ft_putstr_fd("MAP ERROR", 2);
		ft_putchar_fd('\n', 2);
	}
	free_scene(scene);
	exit(0);
}

void	error_v3(t_scene *scene, char *arg)
{
	if (scene != NULL)
	{
		ft_putstr_fd("MAP ERROR: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putchar_fd('\n', 2);
	}
	free_scene(scene);
	exit(0);
}
