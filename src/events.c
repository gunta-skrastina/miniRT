/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 08:31:39 by gskrasti          #+#    #+#             */
/*   Updated: 2023/06/12 13:33:41 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	ft_hook(int event, t_window *mlx)
{
	if (event == 17)
		ft_close(mlx);
	return (0);
}

int	ft_key_hook(int keycode, t_window *mlx)
{
	if (keycode == 53)
		ft_close(mlx);
	if (keycode == 123)
		return (ft_move_left(mlx));
	if (keycode == 124)
		return (ft_move_right(mlx));
	if (keycode == 125)
		return (ft_move_down(mlx));
	if (keycode == 126)
		return (ft_move_up(mlx));
	if (keycode == 49 || keycode == 36)
		return (ft_zoom_in(mlx));
	if (keycode == 51)
		return (ft_zoom_out(mlx));
	return (0);
}

int	ft_close(t_window *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	exit(0);
	return (0);
}
