/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:45:28 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/20 14:49:39 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	calculate_top_bottom_normals(t_cylinder *cylinder)
{
	cylinder->top_normal = cylinder->normal_vec3;
	cylinder->bottom_normal = negate_vec3(cylinder->normal_vec3);
}

int	intersect_cylinder(t_ray *ray, t_cylinder *cylinder, double *t)
{
	double			t0;
	double			t1;
	t_vec3			hit_point0;
	t_vec3			hit_point1;
	t_discriminant	d;

	calculate_top_bottom_normals(cylinder);
	calculate_discriminant(&d, ray, cylinder);
	if (d.discriminat < 0)
		return (0);
	t0 = (-1 * d.b - sqrt(d.discriminat)) / (2.0 * d.a);
	t1 = (-1 * d.b + sqrt(d.discriminat)) / (2.0 * d.a);
	hit_point0 = add_vec3_vec3(ray->origin, multiply_vec3(ray->direction, t0));
	hit_point1 = add_vec3_vec3(ray->origin, multiply_vec3(ray->direction, t1));
	if ((hit_point0.y < (cylinder->center.y - cylinder->height / 2)
			&& hit_point1.y < (cylinder->center.y - cylinder->height / 2))
		|| (hit_point0.y > (cylinder->center.y + cylinder->height / 2)
			&& hit_point1.y > (cylinder->center.y + cylinder->height / 2)))
		return (0);
	*t = fmin(t0, t1);
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
	d->discriminat = disc;
}

void	draw_cylinder(int index, t_vec3 *color, t_scene *scene, t_vec3 hit_vec3)
{
	t_vec3		normal;
	t_vec3		light_direction;
	double		diffuse_factor;
	t_cylinder	*cylinder;

	cylinder = scene->cylinder + index;
	light_direction = subtract_vec3(scene->light->light_point, hit_vec3);
	light_direction = normalize_vec3(light_direction);
	if (hit_vec3.y < (cylinder->center.y - cylinder->height / 2) + 0.1)
		normal = cylinder->bottom_normal;
	else if (hit_vec3.y > (cylinder->center.y + cylinder->height / 2) - 0.1)
		normal = cylinder->top_normal;
	else
		normal = calculate_normal(hit_vec3, cylinder->center);
	diffuse_factor = dot(normal, light_direction)
		* scene->light->light_brightness;
	color->x = (int)(diffuse_factor * cylinder->color.x);
	color->y = (int)(diffuse_factor * cylinder->color.y);
	color->z = (int)(diffuse_factor * cylinder->color.z);
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
