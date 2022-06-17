# include "visu_hex.h"
/*
static void	line(int x1, int y1, int x2, int y2)
{
	int	x = x1;
	int y = y1;

	//gotoxy(x1, y1);
	if (y1 == y2)
	{
		while (x <= x2)
		{
			ft_printf('_');
			++x;
		}
	}
	else if (x1 == x2)
	{
		// while (x <= x2)
		// {
		// 	ft_printf('\r_')
		// 	++x;
		// }
	}
	else
	{
		// while (x <= x2)
		// {
		// 	ft_printf('\r_')
		// 	++x;
		// }
	}
}*/

static void	rectangle(t_data *data, int orig_x, int orig_y, int index)
{
	int x = orig_x;
	int y = orig_y;

	int i = 1;
	int j;
	while (i < 4)
	{
		j = 0;
		while (j < 3)
		{
			if (i == 2 && j == 1)
				data->board[y + i][x + j] = data->room[index] + '0';
			else
				data->board[y + i][x + j] = '-';
			++j;
		}
		++i;
	}
}

void	make_visual(t_data *data)
{
	if (data)
		ft_printf("make visuals\n");
	int i = 0;
	while (i < data->room_total)
	{
		rectangle(data, data->room_x[i], data->room_y[i], i);
		++i;
	}
	i = 0;
	while (data->board[i] != 0)
	{
		ft_printf("%s\n", data->board[i]);
		++i;
	}
	//line(13, 2, 1, 2);
	//  int gd = DETECT, gm, i, a;
  
    // // Path of the program
    // initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");
  
    // // Move the cycle
    // for (i = 0; i < 600; i++) {
    //     // Upper body of cycle
    //     line(50 + i, 405, 100 + i, 405);
    //     line(75 + i, 375, 125 + i, 375);
    //     line(50 + i, 405, 75 + i, 375);
    //     line(100 + i, 405, 100 + i, 345);
    //     line(150 + i, 405, 100 + i, 345);
    //     line(75 + i, 345, 75 + i, 370);
    //     line(70 + i, 370, 80 + i, 370);
    //     line(80 + i, 345, 100 + i, 345);
  
    //     // Wheel
    //     circle(150 + i, 405, 30);
    //     circle(50 + i, 405, 30);
  
    //     // Road
    //     line(0, 436, getmaxx(), 436);
  
    //     // Stone
    //     rectangle(getmaxx() - i, 436,
    //               650 - i, 431);
  
    //     // Stop the screen for 10 secs
    //     delay(10);
  
    //     // Clear the screen
    //     cleardevice();
    // }
  
    // getch();
  
    // // Close the graph
    // closegraph();
}
