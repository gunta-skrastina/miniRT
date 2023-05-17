/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:31:19 by gskrasti          #+#    #+#             */
/*   Updated: 2023/05/17 14:30:37 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    MINIRT_H
# define MINIRT_H

# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_data
{
	void	*img;
	void	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

typedef struct s_window
{
	void	*mlx;
	void	*mlx_win;
	int		height;
	int		width;
	t_data	img;
}			t_window;

typedef struct s_color
{
	double	t;
	double	r;
	double	g;
	double	b;
	int		color;
}			t_color;

typedef	struct s_vec3
{
	double	x;
	double	y;
	double	z;
} t_vec3;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
} t_sphere;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
} t_ray;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_new_img(t_window *mlx);
int		ft_close(t_window *mlx);
int		ft_key_hook(int keycode, t_window *mlx);
int		ft_hook(int event, t_window *mlx);

int		intersectSphere(t_ray ray, t_sphere sphere, double *t);

#endif