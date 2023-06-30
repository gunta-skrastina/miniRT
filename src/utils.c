/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:45:44 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/30 14:33:14 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	swap_t(double *t0, double *t1)
{
	double	*temp;

	if (t0 > t1)
	{
		temp = t0;
		t0 = t1;
		t1 = temp;
	}
}

void	init_ray(t_camera *camera, int i, int j, t_ray *ray)
{
	t_vec2	viewport;
	t_vec3	direction;
	t_vec3	camera_forward;
	t_vec3	camera_right;
	t_vec3	camera_up;

	viewport = canvas_to_viewport(i, j, camera);
	direction.x = viewport.x;
	direction.y = viewport.y;
	direction.z = 1.0;
	camera_forward = normalize_vec3(camera->normal_vec3);
	camera_right = cross(vec3_init(0, 1, 0), camera_forward);
	camera_right = normalize_vec3(camera_right);
	camera_up = cross(camera_forward, camera_right);
	ray->direction.x = direction.x * camera_right.x + direction.y * camera_up.x
		+ direction.z * camera_forward.x;
	ray->direction.y = direction.x * camera_right.y + direction.y * camera_up.y
		+ direction.z * camera_forward.y;
	ray->direction.z = direction.x * camera_right.z + direction.y * camera_up.z
		+ direction.z * camera_forward.z;
	ray->origin = camera->viewpoint;
	ray->direction = normalize_vec3(ray->direction);
}

void	calculate_t(double a, double b, double discriminant, double *t)
{
	double	t0;
	double	t1;

	t0 = (-b - sqrt(discriminant)) / (2 * a);
	t1 = (-b + sqrt(discriminant)) / (2 * a);
	if (t0 >= 0 && t0 < t1)
		*t = t0;
	else if (t1 >= 0)
		*t = t1;
	else
		*t = -1;
}

t_vec3	negate_vec3(t_vec3 vec3)
{
	vec3.x *= -1;
	vec3.y *= -1;
	vec3.z *= -1;
	return (vec3);
}
