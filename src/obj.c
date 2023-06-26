/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:29:22 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/26 06:44:26 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	find_closest_object(t_scene *scene, t_ray *ray, t_obj *closest_obj)
{
	int		closest_sphere;
	int		closest_cylinder;
	int		closest_plane;
	double	t;

	closest_obj->t = INFINITY;
	closest_obj->name = 'n';
	closest_obj->index = -1;
	closest_sphere = find_closest_sphere(scene, ray, &t);
	if (t < closest_obj->t)
	{
		closest_obj->t = t;
		closest_obj->index = closest_sphere;
		closest_obj->name = 's';
	}
	closest_cylinder = find_closest_cylinder(scene, ray, &t);
	if (t < closest_obj->t)
	{
		closest_obj->t = t;
		closest_obj->index = closest_cylinder;
		closest_obj->name = 'c';
	}
	closest_plane = find_closest_plane(scene, ray, &t);
	if (t < closest_obj->t)
	{
		closest_obj->t = t;
		closest_obj->index = closest_plane;
		closest_obj->name = 'p';
	}
}
