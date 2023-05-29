/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:31:19 by gskrasti          #+#    #+#             */
/*   Updated: 2023/05/29 15:57:21 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "graphics.h"
# include "vec3.h"
# include "color.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_color
{
	double	t;
	double	r;
	double	g;
	double	b;
	int		color;
}			t_color;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
}	t_sphere;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

int		intersect_sphere(t_ray ray, t_sphere sphere, double *t);


#endif