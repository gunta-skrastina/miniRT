/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 11:50:39 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/16 15:33:35 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_move_right(t_window *mlx)
{	
	t_scene	*scene;

	scene = mlx->scene;
	mlx->scene->camera->viewpoint.x += scene->zoom_factor;
	ft_new_img(mlx, scene);
	return (0);
}

int	ft_move_left(t_window *mlx)
{	
	t_scene	*scene;

	scene = mlx->scene;
	mlx->scene->camera->viewpoint.x -= scene->zoom_factor;
	ft_new_img(mlx, scene);
	return (0);
}

int	ft_move_up(t_window *mlx)
{	
	t_scene	*scene;

	scene = mlx->scene;
	mlx->scene->camera->viewpoint.y += scene->zoom_factor;
	ft_new_img(mlx, scene);
	return (0);
}

int	ft_move_down(t_window *mlx)
{	
	t_scene	*scene;

	scene = mlx->scene;
	mlx->scene->camera->viewpoint.y -= scene->zoom_factor;
	ft_new_img(mlx, scene);
	return (0);
}
