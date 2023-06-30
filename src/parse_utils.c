/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:27:16 by fjerinic          #+#    #+#             */
/*   Updated: 2023/06/29 16:37:36 by gskrasti         ###   ########.fr       */
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

void	check_dub(double num, t_scene *scene, int flag)
{
	if (flag == 0)
		return ;
	else if (flag == 1 && (num < 0 || num > 1))
		error_v2(scene);
	else if (flag == 2 && (num < 0 || num > 180))
		error_v2(scene);
	else if (flag == 3 && (num < 1 || num > 10))
		error_v2(scene);
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
		error_v3(scene, "Invalid Light Value");
	else if (flag == 2 && (new.x > 1 || new.x < -1 || new.y > 1 || \
			new.y < -1 || new.z > 1 || new.z < -1 || length_vec3(new) > 1))
		error_v3(scene, "Invalid Normal Vector Value");
	return (new);
}
