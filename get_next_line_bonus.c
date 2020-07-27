/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:22:30 by rpunet            #+#    #+#             */
/*   Updated: 2020/07/27 16:57:17 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line_bonus.h"

char	*ft_line_save(char *save, char **line)
{
	size_t	i;
	char	*aux;

	i = 0;
	while(save && save[i] && save[i] != '\n')
		i++;
	if (save && (i < ft_strlen(save)))
	{
		*line = ft_substr(save, 0, i);
		aux = save;
		save = ft_substr(save, i + 1, (ft_strlen(save) - (i + 1)));
		free(aux);
	}
	else
	{
		*line = save;
		save = NULL;
	}
	return (save);
}

char	*ft_buff_save(char *save, char *buffer)
{
	char	*aux;

	if (!save)
		save = ft_strdup(buffer);
	else
	{
		aux = save;
		save = ft_strjoin(save, buffer);
		free(aux);
	}
	return (save);
}

int	get_next_line(int fd, char **line)
{
	static char	*save[FD_MAX];
	char		*buffer;
	int			byte;

	if (!(buffer = (char *)malloc(sizeof *buffer * (BUFFER_SIZE + 1))))
		return (-1);
	while ((byte = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		buffer[byte] = '\0';
		save[fd] = ft_buff_save(save[fd], buffer);
		if (ft_strchr(buffer, '\n'))
			break;
	}
	free (buffer);
	if (byte <= 0 && !save[fd])
	{
		*line = ft_strdup("");
		return (byte);
	}

	save[fd] = ft_line_save(save[fd], line);
	if (byte == 0 && !save[fd])
	{
		return (0);
	}
	return (1);
}
/*
 int		main(void)
{
	char	*line;
	int		fd;
	// int		fd2;
	// int		fd3;

	// line = "hello world";

	if ((fd = open("files/half_marge_bottom", O_RDONLY)) < 0)
		printf("error in open\n");
	// fd2 = open("text2.txt", O_RDONLY);
	// fd3 = open("text2.txt", O_RDONLY);
	// while (get_next_line(fd, &line))
	// 	printf("%s\n\n\n\n\n", line);

	while (get_next_line(fd, &line))
	{
		printf("%s\n--------------------------------------\n", line);
			free (line);
	}

	//  get_next_line(fd, &line);
	//   printf("%s\n", line);

	free (line);
	return (0);
}


 */
