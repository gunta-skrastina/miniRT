/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:33:18 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/01 11:47:07 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(void)
{
	t_window	mlx;
	t_scene		*scene;

	scene = malloc(sizeof(t_scene));
	scene->amb_light = malloc(sizeof(t_amb_light));
	scene->amb_light->light_ratio = 0.2;
	scene->amb_light->color.x = 255;
	scene->amb_light->color.y = 255;
	scene->amb_light->color.z = 255;
	scene->camera = malloc(sizeof(t_camera));
	scene->camera->viewpoint.x = 0;
	scene->camera->viewpoint.y = 0;
	scene->camera->viewpoint.z = 0;
	scene->camera->normal_vec3.x = 0;
	scene->camera->normal_vec3.y = 0;
	scene->camera->normal_vec3.z = 1;
	scene->camera->fov = 70;
	scene->light = malloc(sizeof(t_light));
	scene->light->light_point.x = -40;
	scene->light->light_point.y = 50;
	scene->light->light_point.z = 0;
	scene->light->light_brightness = 0.6;
	scene->num_spheres = 3;
	scene->sphere = malloc(sizeof(t_sphere) * scene->num_spheres);
	scene->sphere[0].center.x = -4;
	scene->sphere[0].center.y = 0;
	scene->sphere[0].center.z = 20.6;
	scene->sphere[0].radius = 3;
	scene->sphere[0].color.x = 10;
	scene->sphere[0].color.y = 0;
	scene->sphere[0].color.z = 255;
	scene->sphere[1].center.x = 10;
	scene->sphere[1].center.y = 0;
	scene->sphere[1].center.z = 22.6;
	scene->sphere[1].radius = 3;
	scene->sphere[2].color.x = 10;
	scene->sphere[2].color.y = 0;
	scene->sphere[2].color.z = 255;
	scene->sphere[2].center.x = 1;
	scene->sphere[2].center.y = 0;
	scene->sphere[2].center.z = 11.6;
	scene->sphere[2].radius = 3;
	scene->sphere[2].color.x = 10;
	scene->sphere[2].color.y = 0;
	scene->sphere[2].color.z = 255;
	// scene->plane = malloc(sizeof(t_plane));
	// scene->plane->point.x = 0;
	// scene->plane->point.y = 0;
	// scene->plane->point.z = -10;
	// scene->plane->normal_vec3.x = 0;
	// scene->plane->normal_vec3.y = 1;
	// scene->plane->normal_vec3.z = 0;
	// scene->plane->color.x = 0;
	// scene->plane->color.y = 0;
	// scene->plane->color.z = 255;
	// scene->cylinder = malloc(sizeof(t_cylinder));
	// scene->cylinder->center.x = 50;
	// scene->cylinder->center.y = 0;
	// scene->cylinder->center.z = 20.6;
	// scene->cylinder->normal_vec3.x = 0;
	// scene->cylinder->normal_vec3.x = 0;
	// scene->cylinder->normal_vec3.x = 1;
	// scene->cylinder->radius = 7.1;
	// scene->cylinder->height = 21.42;
	// scene->cylinder->color.x = 10;
	// scene->cylinder->color.y = 0;
	// scene->cylinder->color.z = 255;
	mlx.width = 1920;
	mlx.height = 1280;
	scene->camera->height = mlx.height;
	scene->camera->width = mlx.width;
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, mlx.width, mlx.height, "miniRT");
	ft_new_img(&mlx, scene);
	mlx_key_hook(mlx.mlx_win, ft_key_hook, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, ft_close, &mlx);
	mlx_loop(mlx.mlx);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_new_img(t_window *mlx, t_scene *scene)
{
	int			i;
	int			j;
	int			color;
	t_ray		ray;
	double		t;
	t_vec3		hit_point;
	t_vec3		normal;
	t_vec2		viewport;
	int			closest_sphere_index;
	double		closest_t;
	int			k;

	mlx->img.img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	j = mlx->height - 1;
	ray.origin.x = scene->camera->viewpoint.x;
	ray.origin.y = scene->camera->viewpoint.y;
	ray.origin.z = scene->camera->viewpoint.z;
	while (j > 0)
	{
		i = 0;
		while (i < mlx->width)
		{
			viewport = canvas_to_viewport(i, j, scene->camera);
			ray.direction.x = viewport.x + scene->camera->normal_vec3.x;
			ray.direction.y = viewport.y + scene->camera->normal_vec3.y;
			ray.direction.z = scene->camera->normal_vec3.z;
			ray.direction = normalize_vec3(ray.direction);
			color = 0x00555555;
			closest_t = INFINITY;
			closest_sphere_index = -1;
			k = 0;
			while (k < scene->num_spheres)
			{
				if (intersect_sphere(ray, scene->sphere[k], &t))
				{
					if (t < closest_t || closest_sphere_index == -1)
					{
						closest_t = t;
						closest_sphere_index = k;
					}
				}
				k++;
			}
			if (closest_sphere_index > -1)
			{
				hit_point = add_vec3_vec3(ray.origin, multiply_vec3(ray.direction, closest_t));
				normal = calculate_normal(hit_point, scene->sphere[closest_sphere_index].center);
				color = convert_to_rgb(normal);
			}
			my_mlx_pixel_put(&mlx->img, i, j, color);
			i++;
		}
		j--;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.img, 0, 0);
	return (0);
}

t_vec3	calculate_normal(t_vec3 hit_point, t_vec3 sphere_center)
{
	t_vec3	normal;

	normal = subtract_vec3(hit_point, sphere_center);
	normal = normalize_vec3(normal);
	return (normal);
}

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
