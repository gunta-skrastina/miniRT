/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:08:25 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/27 14:52:53 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	intersect_sphere(t_ray *ray, t_sphere *sphere, double *t)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;

	a = dot(ray->direction, ray->direction);
	b = 2 * dot(ray->direction, subtract_vec3(ray->origin, sphere->center));
	c = dot(sphere->center, sphere->center) + dot(ray->origin, ray->origin)
		- 2 * dot(sphere->center, ray->origin)
		- sphere->radius * sphere->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	calculate_t(a, b, discriminant, t);
	if (t < 0)
		return (0);
	return (1);
}

void	draw_sphere(int index, t_vec3 *color, t_scene *scene, t_vec3 hit_point)
{
	t_vec3		normal;
	t_vec3		light_direction;
	double		diffuse_factor;

	normal = calculate_normal(hit_point, scene->sphere[index].center);
	light_direction = subtract_vec3(scene->light->light_point, hit_point);
	light_direction = normalize_vec3(light_direction);
	diffuse_factor = dot(normal, light_direction)
		* scene->light->light_brightness;
	color->x = (int)(diffuse_factor * scene->sphere[index].color.x);
	color->y = (int)(diffuse_factor * scene->sphere[index].color.y);
	color->z = (int)(diffuse_factor * scene->sphere[index].color.z);
}

int	find_closest_sphere(t_scene *scene, t_ray *ray, double *t_out)
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
		if (intersect_sphere(ray, scene->sphere + k, &t))
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
