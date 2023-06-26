/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 14:29:22 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/26 20:33:25 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	find_closest_object(t_scene *scene, t_ray *ray, t_obj *obj)
{
	int		closest_sphere;
	int		closest_cylinder;
	int		closest_plane;
	double	t;

	obj->t = INFINITY;
	obj->name = 'n';
	obj->index = -1;
	closest_sphere = find_closest_sphere(scene, ray, &t);
	if (t < obj->t)
		closest_obj(obj, t, closest_sphere, 's');
	closest_cylinder = find_closest_cylinder(scene, ray, &t);
	if (t < obj->t)
		closest_obj(obj, t, closest_cylinder, 'c');
	closest_plane = find_closest_plane(scene, ray, &t);
	if (t < obj->t)
		closest_obj(obj, t, closest_plane, 'p');
}

void	closest_obj(t_obj *obj, double t, int index, char name)
{
	obj->t = t;
	obj->index = index;
	obj->name = name;
}
