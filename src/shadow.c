/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:38:39 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/26 20:20:28 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	is_shadow(t_vec3 hit_point, t_scene *scene, t_obj *object)
{
	t_light	*light;
	t_ray	shadow_ray;
	t_obj	obj;

	light = scene->light;
	shadow_ray.direction = subtract_vec3(light->light_point, hit_point);
	shadow_ray.direction = normalize_vec3(shadow_ray.direction);
	shadow_ray.origin = hit_point;
	closest_shdw(scene, &shadow_ray, object, &obj);
	if (obj.name != 'n' && obj.t > 0.001)
	{
		if (obj.name == object->name && obj.index == object->index)
		{
			return (0);
		}
		return (1);
	}
	return (0);
}

void	closest_shdw(t_scene *scene, t_ray *ray, t_obj *current, t_obj *obj)
{
	int		closest_sphere;
	int		closest_cylinder;
	double	t;

	obj->t = INFINITY;
	obj->name = 'n';
	obj->index = -1;
	closest_sphere = closest_shdw_sphere(scene, ray, &t, current);
	if (t < obj->t)
	{
		obj->t = t;
		obj->index = closest_sphere;
		obj->name = 's';
	}
	closest_cylinder = closest_shdw_cylinder(scene, ray, &t, current);
	if (t < obj->t)
	{
		obj->t = t;
		obj->index = closest_cylinder;
		obj->name = 'c';
	}
}

int	closest_shdw_sphere(t_scene *scene, t_ray *ray, double *t, t_obj *current)
{
	int			closest_sphere_index;
	double		closest_t;
	int			k;

	closest_t = INFINITY;
	closest_sphere_index = -1;
	k = 0;
	while (k < scene->num_spheres)
	{
		if (current->name == 's' && current->index == k)
			k++;
		else if (k < scene->num_spheres
			&& intersect_sphere(ray, scene->sphere + k, t))
		{
			if (*t < closest_t || closest_sphere_index == -1)
			{
				closest_t = *t;
				closest_sphere_index = k;
			}
		}
		k++;
	}
	*t = closest_t;
	return (closest_sphere_index);
}

int	closest_shdw_cylinder(t_scene *scene, t_ray *ray, double *t, t_obj *current)
{
	int			closest_cylinder_index;
	double		closest_t;
	int			k;

	closest_t = INFINITY;
	closest_cylinder_index = -1;
	k = 0;
	while (k < scene->num_cylinders)
	{
		if (current->name == 'c' && current->index == k)
			k++;
		if (k < scene->num_cylinders
			&& intersect_cylinder(ray, scene->cylinder + k, t))
		{
			if (*t < closest_t || closest_cylinder_index == -1)
			{
				closest_t = *t;
				closest_cylinder_index = k;
			}
		}
		k++;
	}
	*t = closest_t;
	return (closest_cylinder_index);
}

int	closest_shdw_plane(t_scene *scene, t_ray *ray, double *t, t_obj *current)
{
	int			closest_plane_index;
	double		closest_t;
	int			k;

	closest_t = INFINITY;
	closest_plane_index = -1;
	k = 0;
	while (k < scene->num_planes)
	{
		if (current->name == 'c' && current->index == k)
			k++;
		if (k < scene->num_planes && intersect_plane(ray, scene->plane + k, t))
		{
			if (*t < closest_t || closest_plane_index == -1)
			{
				closest_t = *t;
				closest_plane_index = k;
			}
		}
		k++;
	}
	*t = closest_t;
	return (closest_plane_index);
}
