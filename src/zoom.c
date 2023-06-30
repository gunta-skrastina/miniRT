/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:56:59 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/29 16:47:53 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_zoom_in(t_window *mlx)
{
	t_scene	*scene;

	scene = mlx->scene;
	mlx->scene->camera->viewpoint.z -= scene->zoom_factor;
	ft_new_img(mlx, scene);
	return (0);
}

int	ft_zoom_out(t_window *mlx)
{
	t_scene	*scene;

	scene = mlx->scene;
	mlx->scene->camera->viewpoint.z += scene->zoom_factor;
	ft_new_img(mlx, scene);
	return (0);
}
