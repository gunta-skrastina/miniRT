/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:38:39 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/26 19:40:35 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	is_shadow(t_vec3 hit_point, t_scene *scene, t_obj *object)
{
	t_light *light;
	t_ray	shadow_ray;
	t_obj	obj;

	light = scene->light;
	shadow_ray.direction = subtract_vec3(light->light_point, hit_point);
	shadow_ray.direction = normalize_vec3(shadow_ray.direction);
	shadow_ray.origin = hit_point;
	find_closest_shadow(scene, &shadow_ray, object, &obj);
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

void	find_closest_shadow(t_scene *scene, t_ray *ray, t_obj *current_obj, t_obj *closest_obj)
{
	int		closest_sphere;
	int		closest_cylinder;
	double	t;

	closest_obj->t = INFINITY;
	closest_obj->name = 'n';
	closest_obj->index = -1;
	closest_sphere = find_closest_shadow_sphere(scene, ray, &t, current_obj);
	if (t < closest_obj->t)
	{
		closest_obj->t = t;
		closest_obj->index = closest_sphere;
		closest_obj->name = 's';
	}
	closest_cylinder = find_closest_shadow_cylinder(scene, ray, &t, current_obj);
	if (t < closest_obj->t)
	{
		closest_obj->t = t;
		closest_obj->index = closest_cylinder;
		closest_obj->name = 'c';
	}
}

int	find_closest_shadow_sphere(t_scene *scene, t_ray *ray, double *t_out, t_obj *current_obj)
{
	int			closest_sphere_index;
	double		closest_t;
	int			k;
	double		t;

	closest_t = INFINITY;
	closest_sphere_index = -1;
	k = 0;
	while (k < scene->num_spheres)
	{
		if (current_obj->name == 's' && current_obj->index == k)
			k++;
		else if (k < scene->num_spheres && intersect_sphere(ray, scene->sphere + k, &t))
		{
			if (t < closest_t || closest_sphere_index == -1)
			{
				closest_t = t;
				closest_sphere_index = k;
			}
		}
		k++;
	}
	*t_out = closest_t;
	return (closest_sphere_index);
}

int	find_closest_shadow_cylinder(t_scene *scene, t_ray *ray, double *t_out, t_obj *current_obj)
{
	int			closest_cylinder_index;
	double		closest_t;
	int			k;
	double		t;

	closest_t = INFINITY;
	closest_cylinder_index = -1;
	k = 0;
	while (k < scene->num_cylinders)
	{
		if (current_obj->name == 'c' && current_obj->index == k)
			k++;
		if (k < scene->num_cylinders && intersect_cylinder(ray, scene->cylinder + k, &t))
		{
			if (t < closest_t || closest_cylinder_index == -1)
			{
				closest_t = t;
				closest_cylinder_index = k;
			}
		}
		k++;
	}
	*t_out = closest_t;
	return (closest_cylinder_index);
}
