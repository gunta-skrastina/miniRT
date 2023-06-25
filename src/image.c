/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 16:30:33 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/25 22:09:55 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_vec2	canvas_to_viewport(int x, int y, t_camera *camera)
{
	t_vec2	viewport;
	double	viewport_width;
	double	viewport_height;

	viewport_width = 2 * tan((camera->fov / 2) * M_PI / 180.0);
	viewport_height = viewport_width * camera->height / camera->width;
	viewport.x = (2 * x / (double)camera->width - 1) * viewport_width / 2;
	viewport.y = (1 - 2 * y / (double)camera->height) * viewport_height / 2;
	return (viewport);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_new_img(t_window *mlx, t_scene *scene)
{
	mlx->img.img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	render_img(mlx, scene);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.img, 0, 0);
	return (0);
}

void	render_img(t_window *mlx, t_scene *scene)
{
	int			i;
	int			j;

	j = mlx->height - 1;
	while (j > 0)
	{
		i = 0;
		while (i < mlx->width)
		{
			render_pixel(mlx, scene, i, j);
			i++;
		}
		j--;
	}
}

void	render_pixel(t_window *mlx, t_scene *scene, int i, int j)
{
	t_ray		ray;
	t_vec3		color;
	t_vec3		hit_point;
	t_obj		obj;

	init_ray(scene->camera, i, j, &ray);
	init_color(&color);
	find_closest_object(scene, &ray, &obj);
	if (obj.name != 'n')
		hit_point = add_vec3_vec3(ray.origin, multiply_vec3(ray.direction, obj.t));
	if (obj.name == 's' && obj.index > -1)
		draw_sphere(obj.index, &color, scene, hit_point);
	else if (obj.name == 'c' && obj.index > -1)
		draw_cylinder(obj.index, &color, scene);
	amb_light(&color, scene);
	if (obj.name != 'n' && obj.t > 0 && is_shadow(hit_point, scene))
	{
		color.x = 255;
		color.y = 192;
		color.z = 42;
		// color.x = 0;
		// color.y = 0;
		// color.z = 0;
	}
	my_mlx_pixel_put(&mlx->img, i, j, convert_to_rgb(color));
}
