/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 09:36:16 by molesen           #+#    #+#             */
/*   Updated: 2021/12/16 15:45:50 by molesen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_not_end_of_str(const int fd, char **str, char **line, int len)
{
	char	*temp;

	*line = ft_strsub(str[fd], 0, len);
	if (!(*line))
	{
		str = ft_free2d(str);
		return (ERROR);
	}
	temp = str[fd];
	str[fd] = ft_strdup(&temp[len + 1]);
	if (!str[fd])
		return (ERROR);
	ft_strdel(&temp);
	if (str[fd][0] == '\0')
		ft_strdel(&str[fd]);
	return (0);
}

static int	ft_str_to_line(const int fd, char **str, char **line)
{
	int	len;

	len = ft_strlen_stop(str[fd], '\n');
	if (str[fd][len] == '\0')
	{
		*line = ft_strdup(str[fd]);
		if (!(*line))
		{
			str = ft_free2d(str);
			return (ERROR);
		}
		ft_strdel(&str[fd]);
	}
	else
		if (ft_not_end_of_str(fd, str, line, len) == ERROR)
			return (ERROR);
	return (0);
}

static int	ft_buf_to_str(const int fd, char **str, char *buf, char **line)
{
	char	*temp;

	if (str[fd])
	{
		temp = str[fd];
		str[fd] = ft_strjoin(temp, buf);
		ft_strdel(&temp);
		if (!str[fd])
		{
			ft_strdel(&str[fd]);
			return (ERROR);
		}
	}
	else
	{
		str[fd] = ft_strdup(buf);
		if (!str[fd])
			return (ERROR);
	}
	if (ft_strchr(str[fd], '\n') != NULL)
		if (ft_str_to_line(fd, str, line) == ERROR)
			return (ERROR);
	return (0);
}

static int	ft_binary_check(char *buf, char *str)
{
	int	i;

	i = 0;
	while (buf[i] != '\0')
	{
		if (ft_isascii(buf[i]) == 1 || ft_isxdigit(buf[i]) == 1)
			return (FALSE);
		if (ft_isoctal(buf[i]) == 1)
			return (FALSE);
		i++;
	}
	if (*str)
		ft_strdel(&str);
	return (TRUE);
}

int	get_next_line(const int fd, char **line)
{	
	static char	*str[FD_SIZE];
	char		buf[BUFF_SIZE + 1];
	int			ret;

	if (fd <= -1 || fd >= FD_SIZE || !line || BUFF_SIZE < 1)
		return (ERROR);
	*line = NULL;
	while ((!str[fd] || ft_strchr(str[fd], '\n') == NULL) && !(*line))
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret <= 0)
			break ;
		buf[ret] = '\0';
		if (ft_binary_check(buf, str[fd]) == TRUE)
			return (0);
		if (ft_buf_to_str(fd, str, buf, line) == ERROR)
			return (ERROR);
	}
	if ((ret == 0 && !str[fd]) && !(*line))
		return (0);
	if (!(*line))
		if (ret == -1 || ft_str_to_line(fd, str, line) == ERROR)
			return (ERROR);
	return (1);
}
