#include "get_next_line.h"

static char	*strappend(char *dst, const char *src, size_t l)
{
	char	*rtn;
	size_t	i;
	size_t	j;
	size_t	k;

	rtn = (char *)malloc(sizeof(char) * (ft_strlen(dst) + l + 1));
	if (!rtn)
		return (NULL);
	i = 0;
	j = 0;
	while (dst[j])
		rtn[i++] = dst[j++];
	k = 0;
	while (k < l)
		rtn[i++] = src[k++];
	rtn[i] = '\0';
	free(dst);
	return (rtn);
}

static t_gnl_status	process_buffer(char *buff, char **line)
{
	const char	*nl_position = ft_strchr(buff, '\n');
	size_t		copy_len;

	if (nl_position)
	{
		copy_len = nl_position - buff;
		*line = strappend(*line, buff, copy_len);
		if (!*line)
			return (GNL_STATUS_ERROR_MALLOC);
		ft_memmove(buff, &buff[copy_len + 1], ft_strlen(&buff[copy_len]) + 1);
		return (GNL_STATUS_SUCCESS);
	}
	*line = strappend(*line, buff, ft_strlen(buff));
	if (!*line)
		return (GNL_STATUS_ERROR_MALLOC);
	return (GNL_NOT_RETURNING);
}

int	get_next_line(int fd, char **line)
{
	static char		buff[(unsigned long)BUFFER_SIZE + 1];
	ssize_t			read_bytes;
	t_gnl_status	status;

	*line = ft_strdup("");
	if (!*line)
		return (GNL_STATUS_ERROR_MALLOC);
	status = GNL_NOT_RETURNING;
	if (buff[0])
		status = process_buffer(buff, line);
	if (status != GNL_NOT_RETURNING)
		return (status);
	while (1)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (GNL_STATUS_ERROR_READ);
		buff[read_bytes] = '\0';
		if (read_bytes == 0)
			return (GNL_STATUS_DONE);
		status = process_buffer(buff, line);
		if (status != GNL_NOT_RETURNING)
			return (status);
	}
}
