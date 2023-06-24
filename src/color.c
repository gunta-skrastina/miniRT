/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:51:03 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/24 01:42:33 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	convert_to_rgb(t_vec3 vec3)
{
	int	color;
	int	r;
	int	g;
	int	b;

	r = clamp(vec3.x, 0, 255);
	g = clamp(vec3.y, 0, 255);
	b = clamp(vec3.z, 0, 255);
	color = r << 16 | g << 8 | b;
	return (color);
}

double	clamp(double num, double min, double max)
{
	if (num < min)
		return (min);
	if (num > max)
		return (max);
	return (num);
}

void	init_color(t_vec3 *color)
{
	color->x = 255;
	color->y = 255;
	color->z = 255;
}
