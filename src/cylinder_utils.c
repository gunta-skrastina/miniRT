/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 22:28:40 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/26 20:50:23 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec3	cross(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3	vec3_init(double x, double y, double z)
{
	t_vec3	vec3;

	vec3.x = x;
	vec3.y = y;
	vec3.z = z;
	return (vec3);
}

void	calculate_top_bottom_normals(t_cylinder *cylinder)
{
	cylinder->top_normal = cylinder->normal_vec3;
	cylinder->bottom_normal = negate_vec3(cylinder->normal_vec3);
}

int	hit_cy(t_cylinder *cy)
{
	if ((cy->hit_point[0].y < (cy->center.y - cy->height / 2)
			&& cy->hit_point[1].y < (cy->center.y - cy->height / 2))
		|| (cy->hit_point[0].y > (cy->center.y + cy->height / 2)
			&& cy->hit_point[1].y > (cy->center.y + cy->height / 2)))
		return (0);
	return (1);
}

int	calculate_hit_cy(t_discriminant *d, double *t, t_cylinder *cy, t_ray *ray)
{
	double	t0;
	double	t1;

	t0 = (-d->b - sqrt(d->discriminant)) / (2.0 * d->a);
	t1 = (-d->b + sqrt(d->discriminant)) / (2.0 * d->a);
	if (t0 >= 0 && (t1 < 0 || t0 < t1))
		*t = t0;
	else if (t1 >= 0 && (t0 < 0 || t1 < t0))
		*t = t1;
	cy->hit_point[0] = vec3_add(ray->origin, multiply_vec3(ray->direction, t0));
	cy->hit_point[1] = vec3_add(ray->origin, multiply_vec3(ray->direction, t1));
	if (hit_cy(cy) == 0)
		return (0);
	if (t0 >= 0 && t0 < t1)
		*t = t0;
	else if (t1 >= 0)
	{
		*t = t1;
		cy->hit_point[0] = cy->hit_point[1];
	}
	else
		return (0);
	return (1);
}
