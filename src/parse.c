/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 16:03:48 by fjerinic          #+#    #+#             */
/*   Updated: 2023/06/27 16:15:13 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

// parses the string and calls different 
// parsing functions based on the content of the string
// checks for illegal identifiers in the map

int	parse(char *str, t_scene *scene)
{
	if (*str == 'p' && *(str + 1) == 'l' && str++)
		parse_plane(&str, scene);
	else if (*str == 'L' && str++)
		parse_light(&str, scene);
	else if (*str == 'A' && str++)
		parse_ambient(&str, scene);
	else if (*str == 'c' && *(str + 1) == 'y' && str++)
		parse_cylinder(&str, scene);
	else if (*str == 'C' && str++)
		parse_camera(&str, scene);
	else if (*str == 's' && *(str + 1) == 'p' && str++)
		parse_sphere(&str, scene);
	else if (*str != '#')
	{
		print_error("no such identifier:");
		return (print_error(str));
	}
	return (1);
}

// initialization of t_scene struct

void	create_scene(t_scene **scene)
{
	(*scene) = (t_scene *)malloc(sizeof(t_scene));
	(*scene)->num_spheres = 0;
	(*scene)->num_planes = 0;
	(*scene)->num_cylinders = 0;
	(*scene)->light = NULL;
	(*scene)->height = 1080;
	(*scene)->width = 1920;
}

void	count_objects(char *str, t_scene *scene)
{
	if (*str == 'p' && *(str + 1) == 'l' && str++)
		scene->num_planes++;
	else if (*str == 'c' && *(str + 1) == 'y' && str++)
		scene->num_cylinders++;
	else if (*str == 's' && *(str + 1) == 'p' && str++)
		scene->num_spheres++;
}

// Opens a file, reads its contents line by line, 
// parses each line using the parse function, 
// updates the scene accordingly. 

t_scene	*parse_scene(char *file_name)
{
	int		fd;
	char	*str;
	t_scene	*scene;

	fd = open(file_name, O_RDONLY);
	scene = NULL;
	if (fd == -1)
		fatal_error("file doesn't exist");
	create_scene(&scene);
	// mlx_init(scene);
	str = get_next_line(fd);
	while (str)
	{
		count_objects(str, scene);
		ft_putstr_fd(str, 2);
		if (*str != '\n')
			if (parse(str, scene) == -1)
				parse_error(scene, fd);
		free(str);
		str = get_next_line(fd);
	}
	free(str);
	close(fd);
	return (scene);
}
