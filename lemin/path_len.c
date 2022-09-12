#include "../includes/lemin.h"

/*	function that creates the len array	*/

int	create_len(int *array, int **len)
{
	int	i;

	i = 0;
	while (array[i] != -1)
	{
		i++;
	}
	*len = (int *)malloc(sizeof(int) * (i + 1));
	if (!(*len))
		return (ERROR);
	i = 0;
	while (array[i] != -1)
	{
		(*len)[i] = 0;
		++i;
	}
	(*len)[i] = -1;
	return (1);
}

/*	resets array to containing all zeros	*/

void	reset_len(t_room *pass, int **len)
{
	int	i;

	i = 0;
	while ((*len)[i] != -1)
	{
		(*len)[i] = 0;
		++i;
	}
	i = 0;
	while (i < pass->total)
	{
		if (pass->info[PATH][i] != 2)
			pass->info[LEN][i] = 0;
		++i;
	}
}

/*	sorts the len array to make sure the smallest is at the beginning of the array	*/

static void	bubble_len(t_room *pass, int **len)
{
	int	a;
	int	b;
	int	temp;

	a = 0;
	while ((*len)[a] > 0)
	{
		b = a + 1;
		while ((*len)[b] > 0)
		{
			if (pass->info[LEN][(*len)[a]] > pass->info[LEN][(*len)[b]])
			{
				temp = (*len)[a];
				(*len)[a] = (*len)[b];
				(*len)[b] = temp;
			}
			++b;
		}
		++a;
	}
}

/*	array that stores the length of paths as the rooms indx in order	*/

void	calc_len(t_room *pass, int **len)
{
	int	i;
	int	next;
	int	count;
	int	j;

	i = 0;
	j = 0;
	while (pass->links[0][i] >= 0)
	{
		if (pass->info[PATH][pass->links[0][i]] == 2)
		{
			count = 1;
			next = pass->info[NEXT][pass->links[0][i]];
			while (next != 0)
			{
				++count;
				next = pass->info[NEXT][next];
			}
			pass->info[LEN][pass->links[0][i]] = count;
			(*len)[j++] = pass->links[0][i];
		}
		++i;
	}
	bubble_len(pass, len);
}
