/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:45:28 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/26 21:02:45 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	intersect_cylinder(t_ray *ray, t_cylinder *cy, double *t)
{
	t_ray			local_ray;
	t_discriminant	d;

	calculate_rot_mat3(cy);
	local_ray.origin = mat3_multiply_vec3(cy->inverse_rot_mat3,
			subtract_vec3(ray->origin, cy->center));
	local_ray.direction
		= mat3_multiply_vec3(cy->inverse_rot_mat3, ray->direction);
	calculate_discriminant(&d, &local_ray, cy);
	if (d.discriminant < 0 || calculate_hit_cy(&d, t, cy, &local_ray) == 0)
		return (0);
	return (1);
}

void	calculate_discriminant(t_discriminant *d, t_ray *ray, t_cylinder *cy)
{
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	disc;

	oc = subtract_vec3(ray->origin, cy->center);
	a = ray->direction.x * ray->direction.x
		+ ray->direction.z * ray->direction.z;
	b = 2.0 * (oc.x * ray->direction.x + oc.z * ray->direction.z);
	c = oc.x * oc.x + oc.z * oc.z - cy->radius * cy->radius;
	disc = b * b - 4 * a * c;
	d->a = a;
	d->b = b;
	d->c = c;
	d->discriminant = disc;
}

int	find_closest_cylinder(t_scene *scene, t_ray *ray, double *t_out)
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
		if (intersect_cylinder(ray, scene->cylinder + k, &t))
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

t_vec3	cy_light_direction(t_cylinder *cy, t_scene *scene)
{
	t_vec3		light_direction;

	light_direction = mat3_multiply_vec3(cy->inverse_rot_mat3,
			subtract_vec3(scene->light->light_point, cy->center));
	light_direction = subtract_vec3(light_direction, cy->hit_point[0]);
	light_direction = normalize_vec3(light_direction);
	return (light_direction);
}

void	draw_cylinder(int index, t_vec3 *color, t_scene *scene)
{
	t_vec3		normal;
	t_vec3		light_direction;
	double		diffuse_factor;
	t_cylinder	*cy;
	t_vec3		local_hit_point;

	cy = scene->cylinder + index;
	light_direction = cy_light_direction(cy, scene);
	if (cy->hit_point[0].y < (cy->center.y - cy->height / 2) + 0.001)
		normal = vec3_init(0, -1, 0);
	else if (cy->hit_point[0].y > (cy->center.y + cy->height / 2) - 0.001)
		normal = vec3_init(0, 1, 0);
	else
	{
		local_hit_point = mat3_multiply_vec3(cy->inverse_rot_mat3,
				subtract_vec3(cy->hit_point[0], cy->center));
		normal = calculate_normal(local_hit_point, vec3_init(0, 0, 0));
		normal = mat3_multiply_vec3(cy->rot_mat3, normal);
	}
	diffuse_factor = clamp(dot(normal, light_direction), 0, 1);
	color->x = (int)(diffuse_factor * cy->color.x);
	color->y = (int)(diffuse_factor * cy->color.y);
	color->z = (int)(diffuse_factor * cy->color.z);
}
