/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpunet <rpunet@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 13:22:30 by rpunet            #+#    #+#             */
/*   Updated: 2020/07/27 11:17:51 by rpunet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "get_next_line.h"

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
		free(save[fd]);
		*line = ft_strdup("");
		free(*line);
		return (byte);
	}

	save[fd] = ft_line_save(save[fd], line);
	if (byte == 0 && !save[fd])
	{
		free(save[fd]);
		free(*line);
		return (0);
	}
	free(save[fd]);
	//free(*line);

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

	fd = open("text.txt", O_RDONLY);
	// fd2 = open("text2.txt", O_RDONLY);
	// fd3 = open("text2.txt", O_RDONLY);
	// while (get_next_line(fd, &line))
	// 	printf("%s\n\n\n\n\n", line);

	 get_next_line(fd, &line);
	 printf("%s\n\n\n\n", line);
	 free (line);

	// get_next_line(fd, &line);
	//  printf("%s\n", line);
	// 	get_next_line(fd, &line);
	// printf("%s\n", line);
	// 	get_next_line(fd, &line);
	// printf("%s\n", line);
	// 		get_next_line(fd, &line);
	// printf("%s\n", line);

	// 		get_next_line(fd, &line);
	// printf("%s\n", line);


	// get_next_line(fd3, &line);
	// printf("%s\n", line);

	// int i;
	// i = 123411;
	// char s[12] = "holatu";
	// (void)s;

	// get_next_line(fd2, &line);
	// printf("%s\n", line);


	// get_next_line(fd, &line);
	// printf("%s\n", line);

	// get_next_line(fd2, &line);
	// printf("%s\n", line);


	// get_next_line(fd, &line);
	// printf("%s\n", line);


	// get_next_line(fd2, &line);
	// printf("%s\n", line);


	// get_next_line(fd, &line);
	// printf("%s\n", line);


	// get_next_line(fd2, &line);
	// printf("%s\n", line);


	// get_next_line(fd3, &line);
	// printf("%s\n", line);




	return (0);
}



*/



/* int	main(int argc, char **argv)
{
	int		fd;
	int		ret;
	char	*line;

	//line = ft_strnew(1);
	//(void)argv;

	if (argc == 1)
	{
		fd = 0;
		ret = get_next_line(fd, &line);
			printf("fd:%d, retorno gnl:%d\n, leido: %s", fd, ret, line);
	}

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
			printf("argv[1]:%s\n", argv[1]);
			printf("fd:%d\n", fd);

		ret = get_next_line(fd, &line);
			printf("retorno %d\n, leido %s", ret, line);

	}
	return (0);
}
 */
