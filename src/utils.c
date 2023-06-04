/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:45:44 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/04 18:54:46 by gskrasti         ###   ########.fr       */
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
	t_vec2		viewport;

	viewport = canvas_to_viewport(i, j, camera);
	ray->origin.x = camera->viewpoint.x;
	ray->origin.y = camera->viewpoint.y;
	ray->origin.z = camera->viewpoint.z * (-1);
	ray->direction.x = viewport.x + camera->normal_vec3.x;
	ray->direction.y = viewport.y + camera->normal_vec3.y;
	ray->direction.z = camera->normal_vec3.z;
	ray->direction = normalize_vec3(ray->direction);
}