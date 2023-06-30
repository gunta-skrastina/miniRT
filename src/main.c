/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 10:33:18 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/29 16:50:04 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char *argv[])
{
	t_window	mlx;
	t_scene		*scene;

	if (argc < 2)
		fatal_error("no file");
	if (!ft_strnstr(argv[1], ".rt", ft_strlen(argv[1])))
		fatal_error("incorect file");
	scene = parse_scene(argv[1]);
	scene->zoom_factor = ZOOM;
	mlx.scene = scene;
	mlx.width = WIDTH;
	mlx.height = HEIGHT;
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
