/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:27:16 by fjerinic          #+#    #+#             */
/*   Updated: 2023/06/27 16:19:44 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	next(char **str, t_scene *scene)
{
	while (!(ft_isdigit(**str)))
	{
		if (**str == ',' || **str == '.')
			error_v2(scene);
		if (**str == '-')
			break ;
		if (**str == '\n')
			error_v2(scene);
		(*str)++;
	}
}

// converts string to float

double	dub(char **str, t_scene *scene, int flag)
{
	int		w;
	double	d;
	int		neg;

	w = 0;
	neg = 1;
	if (**str == '-' && *((*str)++))
		neg = -1;
	while (ft_isdigit(**str))
	{
		w = w * 10 + ((**str) - '0');
		(*str)++;
	}
	if (**str == '.')
		(*str)++;
	d = 0.0;
	while (ft_isdigit(**str))
		d = d * 10 + (*((*str)++) - '0');
	while (d >= 1)
		d /= 10;
	d += w;
	check_dub(d * neg, scene, flag);
	return (d * neg);
}

t_vec3	read_vector(char **str, t_scene *scene, int flag)
{
	t_vec3	new;

	new.x = dub(str, scene, 0);
	(*str)++;
	new.y = dub(str, scene, 0);
	(*str)++;
	new.z = dub(str, scene, 0);
	if (flag == 1 && (new.x > 255 || new.x < 0 || new.y > 255 || \
			new.y < 0 || new.z > 255 || new.z < 0))
		error_v2(scene);
	else if (flag == 2 && (new.x > 1 || new.x < -1 || new.y > 1 || \
			new.y < -1 || new.z > 1 || new.z < -1))
		error_v2(scene);
	return (new);
}
