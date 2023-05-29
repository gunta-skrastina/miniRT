/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:51:03 by gskrasti          #+#    #+#             */
/*   Updated: 2023/05/29 16:11:56 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/minirt.h"

int convert_to_rgb(t_vec3 vec3)
{
	int color;
	int r;
	int g;
	int b;
	
	r = 0;
	g = 0;
	b = 0;
	if (vec3.x > 0 && vec3.x < 1)
		r = vec3.x * 255;
	if (vec3.y > 0 && vec3.y < 1)
		g = vec3.y * 255;
	if (vec3.z > 0 && vec3.z < 1)
		b = vec3.z * 255;
	color = r << 16 | g << 8 | b;
	return (color);
}