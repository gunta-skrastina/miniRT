/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjerinic <fjerinic@gmail.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 19:43:57 by fjerinic          #+#    #+#             */
/*   Updated: 2022/05/17 21:05:53 by fjerinic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// temp is edited (by copying it to another array) the beginning 
// up until the next newline character is cut off
// if there is no newline character left over, temp[0] can be set to zero
// in order to signal that all work with temp has been done.

void	copy_buffer(char *buffer)
{
	int		n;
	char	copy[BUFFER_SIZE + 1];

	copy[BUFFER_SIZE] = 0;
	n = 0;
	while (n < BUFFER_SIZE)
		copy[n++] = '\0';
	ft_strcpy(copy, buffer);
	n = 0;
	while (buffer[n] != '\0' && buffer[n] != '\n')
		n++;
	if (n == BUFFER_SIZE && buffer[n] == 0)
		buffer[0] = 0;
	else
		ft_strcpy(buffer, &copy[n + 1]);
	return ;
}

// formats the output so that it only prints until \n (included)

char	*output(char *res, int bytes)
{
	int		n;
	char	*line;

	if (!res)
		return (NULL);
	if (!bytes && !ft_strchr(res, '\n'))
		return (res);
	n = 0;
	while (res[n] != '\n')
		n++;
	line = ft_substr(res, 0, n + 1);
	free(res);
	return (line);
}

// secured version of stringjoin to prevent memory leaks
// works also as strdup if the first argument is zero

char	*join(char *res, char *buffer)
{
	char	*new_string;
	int		n;
	int		x;

	n = 0;
	x = 0;
	new_string = malloc(ft_strlen(res) + ft_strlen(buffer) + 1);
	if (new_string == 0)
		return (NULL);
	if (res)
	{
		while (res[n])
		{	
			new_string[n] = res[n];
			n++;
		}
		free(res);
	}
	while (buffer[x])
		new_string[n++] = buffer[x++];
	new_string[n] = '\0';
	return (new_string);
}

// subfunction to update the result according to
// whether there is something left in temp or not

char	*refresh_result(char *res, char *buffer)
{
	char	*new;

	if (!res)
		new = join(0, buffer);
	else
		new = join(res, buffer);
	return (new);
}

// gnl reads from a given file descriptor a given BUFFER_SIZE to
// a static buffer array called temp. If there is data left in temp
// from the last iteration, it will first be added to result. 
// The read bytes get also added to result.
// If there is nothing left to read (and in temp), or reading was not 
// possible, NULL is returned.

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE +1];
	int			bytes;
	char		*res;

	res = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	if (buffer[0])
		res = ft_strdup(buffer);
	buffer[BUFFER_SIZE] = '\0';
	while (!ft_strchr(res, '\n'))
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (!bytes || bytes == -1)
			break ;
		if (bytes < BUFFER_SIZE)
			buffer[bytes] = '\0';
		res = refresh_result(res, buffer);
	}
	copy_buffer(buffer);
	return (output(res, bytes));
}

// int main (void)
// {
//     int fd_pointer = open ("", O_RDONLY);
//     char *line;
//     line = get_next_line(fd_pointer);
//     // while (line)
//     // {
//         printf("%s", line);
//         // free(line);
//         // line = get_next_line(fd_pointer);
//     // }
//     close(fd_pointer);
//     return (0);
// } 
