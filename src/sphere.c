/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:08:25 by gskrasti          #+#    #+#             */
/*   Updated: 2023/05/29 14:13:10 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	intersect_sphere(t_ray ray, t_sphere sphere, double *t)
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	t0;
	double	t1;
	double	temp;

	a = ray.direction.x * ray.direction.x + ray.direction.y * ray.direction.y + ray.direction.z * ray.direction.z;
	b = 2 * (ray.direction.x * (ray.origin.x - sphere.center.x) + ray.direction.y * (ray.origin.y - sphere.center.y) + ray.direction.z * (ray.origin.z - sphere.center.z));
	c = sphere.center.x * sphere.center.x + sphere.center.y * sphere.center.y + sphere.center.z * sphere.center.z
		+ ray.origin.x * ray.origin.x + ray.origin.y * ray.origin.y + ray.origin.z * ray.origin.z - 2
		* (sphere.center.x * ray.origin.x + sphere.center.y * ray.origin.y + sphere.center.z * ray.origin.z) - sphere.radius * sphere.radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	else
	{
		t0 = (-b - sqrt(discriminant)) / (2 * a);
		t1 = (-b + sqrt(discriminant)) / (2 * a);
	}
	if (t0 > t1)
	{
		temp = t0;
		t0 = t1;
		t1 = temp;
	}
	if (t1 < 0)
		return (0);
	if (t0 < 0)
		*t = t1;
	else
		*t = t0;
	return (1);
}
