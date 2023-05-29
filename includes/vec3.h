/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 15:06:46 by gskrasti          #+#    #+#             */
/*   Updated: 2023/05/29 16:25:47 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	multiply_vec3(t_vec3 vec3, double num);
t_vec3	subtract_vec3(t_vec3 one, t_vec3 two);
t_vec3	mutilply_vec3_vec3(t_vec3 one, t_vec3 two);
t_vec3	add_vec3_vec3(t_vec3 one, t_vec3 two);
t_vec3	add_vec3(t_vec3 vec3, double num);

#endif