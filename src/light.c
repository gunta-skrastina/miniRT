/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:31:11 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/04 16:59:42 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	amb_light(t_vec3 *color, t_scene *scene)
{
	color->x += (int)(scene->amb_light->light_ratio
			* scene->amb_light->color.x);
	color->y += (int)(scene->amb_light->light_ratio
			* scene->amb_light->color.y);
	color->z += (int)(scene->amb_light->light_ratio
			* scene->amb_light->color.z);
}
