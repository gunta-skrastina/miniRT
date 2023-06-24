/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mat3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 02:59:49 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/24 03:03:17 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_mat3	mat3_init(t_vec3 x, t_vec3 y, t_vec3 z)
{
	t_mat3	mat;

	mat.x = x;
	mat.y = y;
	mat.z = z;
	return (mat);
}

t_vec3	mat3_multiply_vec3(t_mat3 mat, t_vec3 vec)
{
	t_vec3	result;

	result.x = dot(mat.x, vec);
	result.y = dot(mat.y, vec);
	result.z = dot(mat.z, vec);
	return (result);
}

t_mat3	mat3_transpose(t_mat3 mat)
{
	t_mat3	result;

	result.x = vec3_init(mat.x.x, mat.y.x, mat.z.x);
	result.y = vec3_init(mat.x.y, mat.y.y, mat.z.y);
	result.z = vec3_init(mat.x.z, mat.y.z, mat.z.z);
	return (result);
}

void	calculate_rot_mat3(t_cylinder *cylinder)
{
	t_vec3	rot_axis;
	double	rot_angle;
	double	cos_theta;
	double	sin_theta;
	double	one_minus_cos_theta;

	rot_axis = cross(vec3_init(0.0, 1.0, 0.0), cylinder->normal_vec3);
	rot_angle = acos(dot(vec3_init(0.0, 1.0, 0.0), cylinder->normal_vec3));
	cos_theta = cos(rot_angle);
	sin_theta = sin(rot_angle);
	one_minus_cos_theta = 1.0 - cos_theta;
	cylinder->rot_mat3 = mat3_init(
			vec3_init(cos_theta + rot_axis.x * rot_axis.x * one_minus_cos_theta,
				rot_axis.x * rot_axis.y * one_minus_cos_theta - rot_axis.z * sin_theta,
				rot_axis.x * rot_axis.z * one_minus_cos_theta + rot_axis.y * sin_theta),
			vec3_init(rot_axis.y * rot_axis.x * one_minus_cos_theta + rot_axis.z * sin_theta,
				cos_theta + rot_axis.y * rot_axis.y * one_minus_cos_theta,
				rot_axis.y * rot_axis.z * one_minus_cos_theta - rot_axis.x * sin_theta),
			vec3_init(rot_axis.z * rot_axis.x * one_minus_cos_theta - rot_axis.y * sin_theta,
				rot_axis.z * rot_axis.y * one_minus_cos_theta + rot_axis.x * sin_theta,
				cos_theta + rot_axis.z * rot_axis.z * one_minus_cos_theta)
			);
	cylinder->inverse_rot_mat3 = mat3_transpose(cylinder->rot_mat3);
}
