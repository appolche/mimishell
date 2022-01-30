#include "pipex.h"

void	show_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(1);
}

char	*gnl_stdin(int fd)
{
	char	*line;
	char	*buffer;
	int		i;
	int		byte_read;
	char	n;

	i = -1;
	buffer = (char *)malloc(BUFFER_SIZE);
	if (!buffer)
		return (NULL);
	byte_read = read(fd, &n, 1);
	while (byte_read > 0 && n != '\n' && n != '\0')
	{
		if (n != '\n' && n != '\0')
			buffer[++i] = n;
		byte_read = read(fd, &n, 1);
	}
	buffer[++i] = '\n';
	buffer[++i] = '\0';
	line = ft_strdup(buffer);
	free(buffer);
	return (line);
}
