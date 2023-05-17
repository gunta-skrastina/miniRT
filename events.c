/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 08:31:39 by gskrasti          #+#    #+#             */
/*   Updated: 2023/04/25 08:53:06 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	return (0);
}

int	ft_close(t_window *mlx)
{
	mlx_destroy_image(mlx->mlx, mlx->img.img);
	mlx_destroy_window(mlx->mlx, mlx->mlx_win);
	exit(0);
	return (0);
}
