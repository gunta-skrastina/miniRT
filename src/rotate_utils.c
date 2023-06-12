/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 16:51:17 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/12 16:51:45 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	calculate_scene_center(t_scene	*scene)
{
	int	objects;
	int	k;

	objects = scene->num_cylinders + scene->num_planes + scene->num_spheres;
	k = 0;
	while (k < scene->num_cylinders)
	{
		scene->center = add_vec3_vec3(scene->center,
				scene->cylinder[k].center);
		k++;
	}
	k = 0;
	while (k < scene->num_spheres)
	{
		scene->center = add_vec3_vec3(scene->center,
				scene->sphere[k].center);
		k++;
	}
	k = 0;
	scene->center = divide_vec3(scene->center, objects);
}

int	ft_zoom_in(t_window *mlx)
{
	mlx->scene->camera->viewpoint.z += mlx->scene->move_speed;
	ft_new_img(mlx, mlx->scene);
	return (0);
}

int	ft_zoom_out(t_window *mlx)
{
	mlx->scene->camera->viewpoint.z -= mlx->scene->move_speed;
	ft_new_img(mlx, mlx->scene);
	return (0);
}
