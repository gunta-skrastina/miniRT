/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 03:38:39 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/25 22:56:18 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	is_shadow(t_vec3 hit_point, t_scene *scene)
{
	t_light *light;
	t_ray	shadow_ray;
	t_obj	obj;

	light = scene->light;
	shadow_ray.direction = subtract_vec3(light->light_point, hit_point);
	shadow_ray.direction = normalize_vec3(shadow_ray.direction);
	shadow_ray.origin = hit_point;
	find_closest_object(scene, &shadow_ray, &obj);
	if (obj.name != 'n' && obj.t > 0.001)
		return (1);
	return (0);
}
