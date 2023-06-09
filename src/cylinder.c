/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:45:28 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/09 15:24:45 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, double *t)
{	
	t_vec3	oc;
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t0;
	double	t1;
	double	y0;
	double	y1;

	oc = subtract_vec3(ray->origin, cylinder->center);
	a = ray->direction.x * ray->direction.x + ray->direction.z * ray->direction.z;
	b = 2.0 * (oc.x * ray->direction.x + oc.z * ray->direction.z);
	c = oc.x * oc.x + oc.z * oc.z - cylinder->radius * cylinder->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	t0 = (-b - sqrt(discriminant)) / (2.0 * a);
	t1 = (-b + sqrt(discriminant)) / (2.0 * a);
	y0 = ray->origin.y + t0 * ray->direction.y;
	y1 = ray->origin.y + t1 * ray->direction.y;
	if ((y0 < cylinder->center.y || y0 > cylinder->center.y + cylinder->height)
		&& (y1 < cylinder->center.y || y1 > cylinder->center.y + cylinder->height))
		return (0);
	if (y0 > cylinder->center.y)
		*t = t0;
	else
		*t = t1;
	return (1);
}

void	draw_cylinder(int index, t_vec3 *color, t_scene *scene, t_vec3 hit_vec3)
{
	t_vec3		normal;
	t_vec3		light_direction;
	double		diffuse_factor;

	normal = calculate_normal(hit_vec3, scene->cylinder[index].center);
	light_direction = subtract_vec3(scene->light->light_point, hit_vec3);
	light_direction = normalize_vec3(light_direction);
	diffuse_factor = dot(normal, light_direction)
		* scene->light->light_brightness;
	color->x = (int)(diffuse_factor * scene->cylinder[index].color.x);
	color->y = (int)(diffuse_factor * scene->cylinder[index].color.y);
	color->z = (int)(diffuse_factor * scene->cylinder[index].color.z);
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
