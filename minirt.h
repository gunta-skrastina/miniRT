/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:31:19 by gskrasti          #+#    #+#             */
/*   Updated: 2023/05/17 17:38:11 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef    MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>

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

typedef struct amb_light
{
	double	light_ration;
	t_color	color;
	int		count;
} t_amb_light;

typedef struct s_camera
{
	t_vec3	view_point;
	t_vec3	normal_vec3;
	double	fov;
	int		count;
} t_camera;

typedef struct s_light
{
	t_vec3	light_point;
	double	light_brightness;
	int		count;
} t_light;

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_color	color;
	int		count;
} t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	normal_vec3;
	t_color	color;
	int		count;
} t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	normal_vec3;
	double	radius;
	double	hight;
	t_color	color;
	int		count;
} t_cylinder;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
} t_ray;

typedef struct s_scene
{
	t_amb_light	amb_light;
	t_camera	camera;
	t_light		light;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;
}	t_scene;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_new_img(t_window *mlx, t_scene *scene);
int		ft_close(t_window *mlx);
int		ft_key_hook(int keycode, t_window *mlx);
int		ft_hook(int event, t_window *mlx);

int		intersectSphere(t_ray ray, t_sphere sphere, double *t);

int		parse(char *file, t_scene *scene);
int		check_if_rt(char *str);

size_t	ft_strlen(const char *c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strncmp(const char *str1, const char *str2, size_t n);

int		amb_light(char *str, t_scene *scene);
int		camera(char *str, t_scene *scene);
int		light(char *str, t_scene *scene);
int		sphere(char *str, t_scene *scene);
int		plane(char *str, t_scene *scene);
int		cylinder(char *str, t_scene *scene);


#endif