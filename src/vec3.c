/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:04:07 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/04 16:34:00 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec3	add_vec3_vec3(t_vec3 one, t_vec3 two)
{
	t_vec3	res;

	res.x = one.x + two.x;
	res.y = one.y + two.y;
	res.z = one.z + two.z;
	return (res);
}

t_vec3	add_vec3(t_vec3 vec3, double num)
{
	t_vec3	res;

	res.x = vec3.x + num;
	res.y = vec3.y + num;
	res.z = vec3.z + num;
	return (res);
}

t_vec3	multiply_vec3_vec3(t_vec3 one, t_vec3 two)
{
	t_vec3	res;

	res.x = one.x * two.x;
	res.y = one.y * two.y;
	res.z = one.z * two.z;
	return (res);
}

t_vec3	multiply_vec3(t_vec3 vec3, double num)
{
	t_vec3	res;

	res.x = vec3.x * num;
	res.y = vec3.y * num;
	res.z = vec3.z * num;
	return (res);
}

t_vec3	subtract_vec3(t_vec3 one, t_vec3 two)
{
	t_vec3	res;

	res.x = one.x - two.x;
	res.y = one.y - two.y;
	res.z = one.z - two.z;
	return (res);
}
