/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:33:26 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/08 18:00:44 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec3	calculate_normal(t_vec3 hit_point, t_vec3 sphere_center)
{
	t_vec3	normal;

	normal = subtract_vec3(hit_point, sphere_center);
	normal = normalize_vec3(normal);
	return (normal);
}

t_vec3	normalize_vec3(t_vec3 vec3)
{
	double	magnitude;

	magnitude = length_vec3(vec3);
	vec3.x /= magnitude;
	vec3.y /= magnitude;
	vec3.z /= magnitude;
	return (vec3);
}

double	dot(t_vec3 one, t_vec3 two)
{
	double	res;

	res = one.x * two.x + one.y * two.y + one.z * two.z;
	return (res);
}

double	length_vec3(t_vec3 vec3)
{
	return (sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z));
}
