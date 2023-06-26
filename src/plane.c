/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 06:33:32 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/26 18:07:33 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	intersect_plane(t_ray *ray, t_plane *plane, double *t)
{
	double	denom;
	t_vec3	plane_to_ray_origin;
	double	distance;
	
    denom = dot(plane->normal_vec3, ray->direction);
    if (fabs(denom) < 0.001)
        return (0);
    plane_to_ray_origin = subtract_vec3(ray->origin, plane->point);
    distance = dot(plane_to_ray_origin, plane->normal_vec3) / denom;
    if (distance < 0)
        return (0);
    *t = distance;
    return (1);
}

int find_closest_plane(t_scene *scene, t_ray *ray, double *t_out)
{
	int			closest_plane_index;
	double		closest_t;
	int			k;
	double		t;

	closest_t = INFINITY;
	closest_plane_index = -1;
	k = 0;
	while (k < scene->num_planes)
	{
		if (intersect_plane(ray, scene->plane + k, &t))
		{
			if (t < closest_t || closest_plane_index == -1)
			{
				closest_t = t;
				closest_plane_index = k;
			}
		}
		k++;
	}
	*t_out = closest_t;
	return (closest_plane_index);
}

void	draw_plane(int index, t_vec3 *color, t_scene *scene)
{
	t_vec3	normal;
	t_vec3	light_direction;
	double	diffuse_factor;
	t_plane	*pl;

	pl = scene->plane + index;
	light_direction = subtract_vec3(scene->light->light_point, pl->point);
	light_direction = normalize_vec3(light_direction);
	normal = pl->normal_vec3;
	diffuse_factor = dot(normal, light_direction);
	if (diffuse_factor < 0)
		diffuse_factor = 0;
	else if (diffuse_factor > 1)
		diffuse_factor = 1;
	color->x = (int)(diffuse_factor * pl->color.x);
	color->y = (int)(diffuse_factor * pl->color.y);
	color->z = (int)(diffuse_factor * pl->color.z);
}
