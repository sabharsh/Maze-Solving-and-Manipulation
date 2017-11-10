#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "maze_manipulation.h"

void _print(Maze* maze);

int main()//int argc, char* argv[])
{
	char* filename_read  = "maze_sample_15x15.txt";
	char* filename_write = "maze_sample_copy.txt";
	
	//TESTING malloc_maze(...) & free_maze(...)
	Maze* maze = malloc_maze(2, 2);
	maze -> cells[0][0] = '1';
	maze -> cells[0][1] = '2';
	maze -> cells[1][0] = '3';
	maze -> cells[1][1] = '4';
	printf("Testing malloc_maze(...) & free_maze(...):\n");
	_print(maze);
	free_maze(maze);

	//TESTING read_maze(...)
	printf("\nTesting read_maze(...):\n");
	FILE* fp = fopen(filename_read,"r"); //sample FILE opened (Alternate testing file --> "random_maze","r");//)
	Maze* maze2 = read_maze(fp);          //allocated MEMORY to maze2
	_print(maze2);
	fclose(fp);                           //sample FILE closed

	//TESTING write_maze(...)
	printf("\nTesting write_maze(...)\n");
	bool write_success = write_maze(filename_write, maze2);
	if( write_success )
	{
		printf("Write successful.\n");
		FILE * fp2 = fopen(filename_write,"r"); //my sample FILE opened
		Maze* maze3 = read_maze(fp2);                 //allocated MEMORY to maze3
		_print(maze3);
		fclose(fp2);                                  //my sample FILE closed
		free_maze(maze3);                             //freed MEMORY of maze3
	}
	else
	{
		printf("Write unsuccessful.\n");
	}

	//TESTING make_taller(...)
	printf("\nTesting make_taller(...):\n");
	Maze * maze4 = make_taller(maze2);    //allocated MEMORY to maze4
	_print(maze4);
	free_maze(maze4);                     //freed MEMORY of maze4

	//TESTING make_wider(...)
	printf("\nTesting make_wider(...):\n");
	Maze * maze5 = make_wider(maze2);    //allocated MEMORY to maze5
	_print(maze5);
	free_maze(maze5);                     //freed MEMORY of maze5

	free_maze(maze2);                     //freed MEMORY of maze2
}

void _print(Maze* maze)
{
	printf("num_rows: %d\nnum_cols: %d\n", maze -> num_rows, maze -> num_cols);
	for(int i=0; i < maze->num_rows; i++)
	{
		for(int j=0; j < maze->num_cols; j++)
		{
			fputc(maze -> cells[i][j], stdout);
		}
		fputc('\n', stdout);
	}
}
