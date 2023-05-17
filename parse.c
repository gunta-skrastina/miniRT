/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gskrasti <gskrasti@students.42wolfsburg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 14:47:40 by gskrasti          #+#    #+#             */
/*   Updated: 2023/05/17 17:38:30 by gskrasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int check_if_rt(char *str)
{
	int	len;

	len = ft_strlen(str);
	if(!ft_strncmp(ft_substr(str, len - 3, 3), ".rt", 3))
	{
		return(0);
	}
	return (1);
}

int parse(char *file, t_scene *scene)
{
	char	str[100];
	int		fd;
	int		rd;
	int		i;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (1);
	rd = 1;
	while (rd > 0)
	{
		ft_bzero(str, 100);
		i = 0;
		while (!str[0])
		{
			rd = read(fd, str, 1);
			if (str[0] == 32 || str[0] == '\n')
			{
				str[0] = 0;
			}
		}
		while (str[ft_strlen(str) - 1] == '\n')
		{
			rd = read(fd, str + ft_strlen(str), 1);
			printf("tetstfr %s\n", str);
		}
		while (str[ft_strlen(str) - 1] != '\n' && rd > 0)
			rd = read(fd, str + ft_strlen(str), 1);
		str[ft_strlen(str)] = '\0';
		printf("Test: %s\n", str);
		if (str[i] == 'A')
		{
			if(amb_light(str, scene))
				return (1);
		}
		// else if (str[i] == 'C')
		// 	str = camera(str, scene);
		// else if (str[i] == 'L')
		// 	str = light(str, scene);
		// else if (str[i] == 's' && str[i + 1] == 'p')
		// 	str = sphere(str, scene);
		// else if (str[i] == 'p' && str[i + 1] == 'l')
		// 	str = plane(str, scene);
		// else if (str[i] == 'c' && str[i + 1] == 'y')
		// 	str = cylinder(str, scene);
		// else if (str[i] == '\t')
		// 	i++;
		// else
		// 	return (2);
	}
	// free(str);
	return (0);
}

int	amb_light(char *str, t_scene *scene)
{
	int		i;
	char	**split;

	scene->amb_light.count++;
	if (scene->amb_light.count > 1 || str[1] != 32)
		return (1);
	i = 1;
	while(str[i] == 32)
		i++;
	split = ft_split(str + i, 32);
	
	return(0);
}

// int	camera(char *str, t_scene *scene)
// {
// 	return(str);
// }

// int	light(char *str, t_scene *scene)
// {
// 	return(str);
// }

// int	sphere(char *str, t_scene *scene)
// {
// 	return(str);
// }

// int	plane(char *str, t_scene *scene)
// {
// 	return(str);	
// }

// int	cylinder(char *str, t_scene *scene)
// {
// 	return(str);
// }
