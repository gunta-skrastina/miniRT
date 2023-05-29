/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:48:43 by gskrasti          #+#    #+#             */
/*   Updated: 2023/05/29 13:53:52 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_new_img(t_window *mlx);
int		ft_close(t_window *mlx);
int		ft_key_hook(int keycode, t_window *mlx);
int		ft_hook(int event, t_window *mlx);

#endif