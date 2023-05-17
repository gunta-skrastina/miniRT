/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:33:18 by gskrasti          #+#    #+#             */
/*   Updated: 2023/05/17 14:29:56 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	t_window	mlx;

	mlx.width = 1920;
	mlx.height= 1280;
	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, mlx.width, mlx.height, "miniRT");
	ft_new_img(&mlx);
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

int	ft_new_img(t_window *mlx)
{
	int			i;
	int			j;
	t_color		color;
	t_ray		ray;
	t_sphere	sphere;
	double		t;

	mlx->img.img = mlx_new_image(mlx->mlx, mlx->width, mlx->height);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &mlx->img.bits_per_pixel,
			&mlx->img.line_length, &mlx->img.endian);
	j = mlx->height - 1;
	color.b = 0.25;
	ray.origin.x = 0.0;
	ray.origin.y = 0.0;
	ray.origin.z = 0.0;
	sphere.center.x = 0.0;
	sphere.center.y = 0.0;
	sphere.center.z = 25.0;
	sphere.radius = 2.0;
	// t_sphere	sphere2;
	// sphere2.center.x = 2.0;
	// sphere2.center.y = 0.0;
	// sphere2.center.z = 25.0;
	// sphere2.radius = 1.0;
	while (j > 0)
	{
		i = 0;
		while (i < mlx->width)
		{
			ray.direction.x = (2.0 * i / mlx->width) - 1.0;
			ray.direction.y = (2.0 * j / mlx->height * mlx->height / mlx->width) - 1.0;
			ray.direction.z = 1.0;
			if (intersectSphere(ray, sphere, &t))
			{
				color.color = 0x00660000;
			}
			// else if (intersectSphere(ray, sphere2, &t))
			// {
			// 	color.color = 0x00000066;
			// }
			else
			{
				color.color = 0x00006600;
			}
			my_mlx_pixel_put(&mlx->img, i, mlx->height - j, color.color);
			i++;
		}
		j--;
	}
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.img, 0, 0);
	return (0);
}
