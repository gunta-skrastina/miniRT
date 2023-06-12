/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 11:02:10 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/12 17:17:34 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_move_left(t_window *mlx)
{
	t_scene		*scene;
	t_vec3		camera_to_center;
	double		distance;
	double		angle;

	scene = mlx->scene;
	camera_to_center = subtract_vec3(scene->center, scene->camera->viewpoint);
	distance = length_vec3(camera_to_center);
	angle = -scene->move_speed * M_PI / 180.0;
	scene->camera->viewpoint.x = scene->center.x
		- (camera_to_center.x * cos(angle) + camera_to_center.z * sin(angle));
	scene->camera->viewpoint.z = scene->center.z
		- (-camera_to_center.x * sin(angle) + camera_to_center.z * cos(angle));
	camera_to_center = subtract_vec3(scene->center, scene->camera->viewpoint);
	camera_to_center = multiply_vec3(normalize_vec3(camera_to_center),
			distance);
	scene->camera->viewpoint = subtract_vec3(scene->center, camera_to_center);
	ft_new_img(mlx, mlx->scene);
	return (0);
}

int	ft_move_right(t_window *mlx)
{
	t_scene		*scene;
	t_vec3		camera_to_center;
	double		distance;
	double		angle;

	scene = mlx->scene;
	camera_to_center = subtract_vec3(scene->center, scene->camera->viewpoint);
	distance = length_vec3(camera_to_center);
	angle = scene->move_speed * M_PI / 180.0;
	scene->camera->viewpoint.x = scene->center.x
		- (camera_to_center.x * cos(angle) + camera_to_center.z * sin(angle));
	scene->camera->viewpoint.z = scene->center.z
		- (-camera_to_center.x * sin(angle) + camera_to_center.z * cos(angle));
	camera_to_center = subtract_vec3(scene->center, scene->camera->viewpoint);
	camera_to_center = multiply_vec3(normalize_vec3(camera_to_center),
			distance);
	scene->camera->viewpoint = subtract_vec3(scene->center, camera_to_center);
	ft_new_img(mlx, mlx->scene);
	return (0);
}

int	ft_move_up(t_window *mlx)
{
	t_scene		*scene;
	t_vec3		camera_to_center;
	double		distance;
	double		angle;

	scene = mlx->scene;
	camera_to_center = subtract_vec3(scene->center, scene->camera->viewpoint);
	distance = length_vec3(camera_to_center);
	angle = scene->move_speed * M_PI / 180.0;
	scene->camera->viewpoint.y = scene->center.y
		- (camera_to_center.y * cos(angle) + camera_to_center.z * sin(angle));
	scene->camera->viewpoint.z = scene->center.z
		- (-camera_to_center.y * sin(angle) + camera_to_center.z * cos(angle));
	camera_to_center = subtract_vec3(scene->center, scene->camera->viewpoint);
	camera_to_center = multiply_vec3(normalize_vec3(camera_to_center),
			distance);
	scene->camera->viewpoint = subtract_vec3(scene->center, camera_to_center);
	ft_new_img(mlx, mlx->scene);
	return (0);
}

int	ft_move_down(t_window *mlx)
{
	t_scene		*scene;
	t_vec3		camera_to_center;
	double		distance;
	double		angle;

	scene = mlx->scene;
	camera_to_center = subtract_vec3(scene->center, scene->camera->viewpoint);
	distance = length_vec3(camera_to_center);
	angle = -scene->move_speed * M_PI / 180.0;
	scene->camera->viewpoint.y = scene->center.y
		- (camera_to_center.y * cos(angle) + camera_to_center.z * sin(angle));
	scene->camera->viewpoint.z = scene->center.z
		- (-camera_to_center.y * sin(angle) + camera_to_center.z * cos(angle));
	camera_to_center = subtract_vec3(scene->center, scene->camera->viewpoint);
	camera_to_center = multiply_vec3(normalize_vec3(camera_to_center),
			distance);
	scene->camera->viewpoint = subtract_vec3(scene->center, camera_to_center);
	ft_new_img(mlx, mlx->scene);
	return (0);
}
