/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:31:19 by gskrasti          #+#    #+#             */
/*   Updated: 2023/05/31 13:57:15 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    MINIRT_H
# define MINIRT_H

# include "mlx.h"
# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
}	t_ray;

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

typedef struct s_amb_light
{
	double	light_ratio;
	t_vec3	color;
}	t_amb_light;

typedef struct s_camera
{
	t_vec3	viewpoint;
	t_vec3	normal_vec3;
	double	fov;
	double	distance;
	int		height;
	int		width;
}	t_camera;

typedef struct s_light
{
	t_vec3	light_point;
	double	light_brightness;
}	t_light;

typedef struct s_sphere
{
	t_vec3	center;
	t_vec3	color;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal_vec3;
	t_vec3	color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	normal_vec3;
	double	radius;
	double	height;
	t_vec3	color;
}	t_cylinder;

typedef struct s_scene
{
	t_amb_light	*amb_light;
	t_camera	*camera;
	t_light		*light;
	int			num_spheres;
	t_sphere	*sphere;
	int			num_planes;
	t_plane		*plane;
	int			num_cylinders;
	t_cylinder	*cylinder;
}	t_scene;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_new_img(t_window *mlx, t_scene *scene);
int		ft_close(t_window *mlx);
int		ft_key_hook(int keycode, t_window *mlx);
int		ft_hook(int event, t_window *mlx);
int		intersect_sphere(t_ray ray, t_sphere sphere, double *t);
t_vec3	multiply_vec3(t_vec3 vec3, double num);
t_vec3	subtract_vec3(t_vec3 one, t_vec3 two);
t_vec3	mutilply_vec3_vec3(t_vec3 one, t_vec3 two);
t_vec3	add_vec3_vec3(t_vec3 one, t_vec3 two);
t_vec3	add_vec3(t_vec3 vec3, double num);
double	dot_product(t_vec3 one, t_vec3 two);
t_vec3	calculate_normal(t_vec3 hit_point, t_vec3 sphere_center);
t_vec3	normalize_vec3(t_vec3 vec3);
int		convert_to_rgb(t_vec3 vec3);
t_vec2	canvas_to_viewport(int x, int y, t_camera *camera);
double	calculate_camera_distance(t_camera *camera);

#endif