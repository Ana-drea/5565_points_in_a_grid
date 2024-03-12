#include <stdio.h>
#include <stdlib.h>

// Name: Huiwen Zhou Student ID: 2094248
// Name: Man Luo Student ID: 2076393
// Name: Qianxin Zhou Student ID: 2086858

int get_nex_coordinate(int grid_x, int x)
{
    // If the quotient of the incoming coordinate before bouncing divided by the width of the grid is even, then the remainder is the real coordinate.
    if (x / (grid_x - 1) % 2 == 0)
    {
        return x % (grid_x - 1);
    }
    else
    {
        // Otherwise, the real coordinate is the remainder number of positions counted from the left boundary; the same applies to the y-axis coordinate.
        return (grid_x - 1) - x % (grid_x - 1);
    }
}

int main()
{
    FILE *input_file = fopen("input.txt", "r");
    FILE *output_file = fopen("output.txt", "w");

    if (input_file == NULL || output_file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    int grid_x, grid_y;
    fscanf(input_file, "%d %d", &grid_x, &grid_y); // read x, y grid
    // fprintf(output_file, "%d\n%d\n", grid_x, grid_y); //把对应长度写入output文件
    // if<=0，error and exit
    if (grid_x <= 0 || grid_y <= 0)
    {
        printf("Invalid input, length and width of grid should be greater than zero.\n");
        fprintf(output_file, "Error\n");
        return 1;
    }
    // create 2-d array according to x, y grid
    int grid[grid_y + 2][grid_x + 2];

    // loop over every position, put '*' in boundary and ' ' in other position
    for (int i = 0; i < grid_y + 2; i++)
    {
        for (int j = 0; j < grid_x + 2; j++)
        {
            grid[i][j] = (i == 0 || i == grid_y + 1 || j == 0 || j == grid_x + 1) ? '*' : ' ';
        }
    }

    int seconds;
    fscanf(input_file, "%d", &seconds); // read seconds
    // if <0，error and exit
    if (seconds < 0)
    {
        printf("Invalid input, number of seconds should be greater than or equal to zero.\n");
        fprintf(output_file, "Error\n");
        return 1;
    }

    int x, y, v_x, v_y;
    // int points[5][3];
    // int num_points = 0;
    // read each point's coordinates and velocity until reach 'E'
    while (fscanf(input_file, "%d,%d,%d,%d", &x, &y, &v_x, &v_y) == 4)
    {
        if (x < 0 || x >= grid_x || y < 0 || y >= grid_y)
        {
            printf("Invalid input, coordinate of points should be between (0,0) and (%d,%d).\n", grid_x - 1, grid_y - 1);
            fprintf(output_file, "Error\n");
            return 1;
        }
        // calculate the position of each point after n seconds and use get_nex_coordinate() to get the coordinate after bouncing
        // use absoltes because coordinates before bouncing can be negative value
        int new_x = get_nex_coordinate(grid_x, abs(x + seconds * v_x));
        int new_y = get_nex_coordinate(grid_y, abs(y + seconds * v_y));
        // fprintf(output_file, "Point at (%d, %d)\n", new_x, new_y);

        // put points into grid
        if (grid[grid_y - new_y][new_x + 1] >= 1 && grid[grid_y - new_y][new_x + 1] <= 5)
        {
            // if other points have already landed at this position, value+1
            grid[grid_y - new_y][new_x + 1] += 1;
        }

        // otherwise set the value to 1
        else if (grid[grid_y - new_y][new_x + 1] == ' ')
        {
            grid[grid_y - new_y][new_x + 1] = 1;
        }
        // check if the next char is 'E'
        int next_char = fgetc(input_file);
        if (next_char == 'E' || next_char == EOF)
        {
            break;
        }
        else
        {
            // put the read char back for next read
            ungetc(next_char, input_file);
        }
    }

    // print the 2-d array with points
    for (int i = 0; i < grid_y + 2; i++)
    {
        for (int j = 0; j < grid_x + 2; j++)
        {
            // if the value is greater than 1, print ' '
            if (grid[i][j] > 1 && grid[i][j] <= 5)
            {
                fprintf(output_file, "%c", ' ');
            }
            // if equal to 1 print '+' 
            else if (grid[i][j] == 1)
            {
                fprintf(output_file, "%c", '+');
            }
            // otherwise print the original value
            else
            {
                fprintf(output_file, "%c", grid[i][j]);
            }
        }
        if (i != grid_y + 1)
        {
            fprintf(output_file, "\n");
        }
    }
    fclose(input_file);
    fclose(output_file);

    return 0;
}