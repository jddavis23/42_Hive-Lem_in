# include "../libft/ft_printf.h"

int	main(void)
{
	int		ret;
	char	*line;

	ret = 1;
	line = NULL;
	while (ret == 1)
	{
		ret = get_next_line(0, &line);
		if (ret == ERROR)
			return (0);
		if (!line)
			break ;
		ft_printf("%s\n", line);
		free(line);
	}
	return (0);
}