/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:07:25 by fjerinic          #+#    #+#             */
/*   Updated: 2023/06/29 15:42:06 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	parse_plane(char **str, t_scene *scene)
{
	t_plane	*plane;

	plane = scene->plane + scene->plane_index;
	next(str, scene);
	plane->point = read_vector(str, scene, 0);
	next(str, scene);
	plane->normal_vec3 = normalize_vec3(read_vector(str, scene, 2));
	next(str, scene);
	plane->color = read_vector(str, scene, 1);
	scene->plane_index++;
}

void	parse_sphere(char **str, t_scene *scene)
{
	t_sphere	*sphere;

	sphere = scene->sphere + scene->sphere_index;
	next(str, scene);
	sphere->center = read_vector(str, scene, 0);
	next(str, scene);
	sphere->radius = dub(str, scene, 2) / 2;
	next(str, scene);
	sphere->color = read_vector(str, scene, 1);
	scene->sphere_index++;
}

void	parse_cylinder(char **str, t_scene *scene)
{
	t_cylinder	*cylinder;

	cylinder = scene->cylinder + scene->cylinder_index;
	next(str, scene);
	cylinder->center = read_vector(str, scene, 0);
	next(str, scene);
	cylinder->normal_vec3 = normalize_vec3(read_vector(str, scene, 2));
	next(str, scene);
	cylinder->radius = dub(str, scene, 0) / 2;
	next(str, scene);
	cylinder->height = dub(str, scene, 0);
	next(str, scene);
	cylinder->color = read_vector(str, scene, 1);
	scene->cylinder_index++;
}
