#include <stdlib.h>
#include "maze_manipulation.h"

void _find_maze_dimensions(FILE* fp, int* num_rows, int* num_cols);

Maze* malloc_maze(int num_rows, int num_cols)
{
	Maze* a_maze = malloc( sizeof(a_maze -> num_rows) +  sizeof(a_maze -> num_cols) + sizeof(a_maze -> cells) );//mallocs for struct
	if(a_maze == NULL)
	{
		return NULL;
	}
	a_maze -> num_rows = num_rows;
	a_maze -> num_cols = num_cols;
	a_maze -> cells    = malloc( sizeof(*(a_maze -> cells)) * num_rows); //mallocs for row array (which stores the address of the column arrays)
	if(a_maze -> cells == NULL)
	{
		free( a_maze );
		return NULL;
	}
	for(int i=0; i<num_rows; i++)
	{
		a_maze -> cells[i] = malloc( sizeof( *(a_maze -> cells[0]) ) * num_cols );//mallocs for each column
		if(a_maze -> cells[i] == NULL)//frees everything in case of malloc error
		{
			for(int j=0; j<i; j++)
			{
				free( a_maze -> cells[j] );
			}
			free( a_maze -> cells);
			free( a_maze );
			return NULL;
		}
	}
	return a_maze;
}
void free_maze(Maze* maze)
{
	for(int i=0; i<(maze -> num_rows); i++)//frees each column
	{
		free( maze -> cells[i] );
	}
	free(maze -> cells);//frees the row array (which stores the addresses of the first char of the column arrays)
	free(maze);//frees the struct
}

Maze* read_maze(FILE* fp)
{
	int num_rows = 0;
	int num_cols = 0;
	_find_maze_dimensions(fp, &num_rows, &num_cols); //calculating maze dimensions using helper function
	Maze* maze = malloc_maze(num_rows, num_cols);
	if(maze == NULL)
	{
		return NULL;
	}
	fseek(fp, 0, SEEK_SET);
	for(int i=0; i<num_rows; i++)
	{
		for(int j=0; j<num_cols; j++)
		{
			char ch = fgetc(fp);
			if(ch == '\n')
			{
				ch = fgetc(fp);
			}
			maze -> cells[i][j] = ch;
		}
	}
	return maze;
}

bool write_maze(const char* filename, const Maze* maze)
{
	FILE * fp = fopen(filename, "w");
	for(int i=0; i < maze -> num_rows; i++)
	{
		for(int j=0; j < maze -> num_cols; j++)
		{
			char ch = fputc(maze -> cells[i][j], fp);
			if(ch == EOF)
			{
				fclose(fp);
				return false;
			}
		}
		fputc('\n',fp); //adding new line character at the end of the row
	}
	fclose(fp);
	return true;
}

Maze* make_taller(const Maze* orig)
{
	Maze * tall_maze = malloc_maze( 2 * orig -> num_rows - 1, orig -> num_cols);
	if(tall_maze == NULL)
	{
		return NULL;
	}
	for(int i=0; i < orig -> num_rows; i++) //fills first horizontal half of the tall_maze
	{
		for(int j=0; j < orig -> num_cols; j++)
		{
			tall_maze -> cells[i][j] = orig -> cells[i][j]; //fills the second vertical half of the tall_maze
		}
	}
	for(int i = orig -> num_rows; i< tall_maze -> num_rows; i++)
	{
		for(int j=0; j < orig -> num_cols; j++)
		{
			tall_maze -> cells[i][j] = orig -> cells[tall_maze -> num_rows - i - 1][j];
		}
	}
	return tall_maze;
}

Maze* make_wider(const Maze* orig)
{
	Maze * wide_maze = malloc_maze(orig -> num_rows, 2 * orig -> num_cols - 1);
	if(wide_maze == NULL)
	{
		return NULL;
	}
	for(int i=0; i < orig -> num_cols; i++) //fills first vertical half of the wide_maze
	{
		for(int j=0; j < orig -> num_rows; j++)
		{
			wide_maze -> cells[j][i] = orig -> cells[j][i];
		}
	}
	for(int i = orig -> num_cols; i< wide_maze -> num_cols; i++) //fills second vertical half of the wide_maze
	{
		for(int j=0; j < orig -> num_rows; j++)
		{
			wide_maze -> cells[j][i] = orig -> cells[j][wide_maze -> num_cols - i - 1];
		}
	}
	for(int direction = -1; direction <=1; direction += 2)//direction decides the direction in which the while loop will traverse
	{
		int pos_r = wide_maze -> num_rows / 2; //begins at center center of maze
		int pos_c = wide_maze -> num_cols / 2;
		bool unified = false;
		while( !unified ) //unifies the widened maze
		{
			if(wide_maze -> cells[pos_r][pos_c] == WALL)
			{
				wide_maze -> cells[pos_r][pos_c] = PATH;//removing wall
			}
			if(wide_maze -> cells[pos_r][pos_c + direction] == PATH || 
			   wide_maze -> cells[pos_r - 1][pos_c] == PATH || 
			   wide_maze -> cells[pos_r + 1][pos_c] == PATH ) //checking surrounding of the current location
			{
				unified = true;
			}
			else
			{
				pos_c += direction; //shifts one left or one right depending on the value of direction
			}
		}
	}
	return wide_maze;
}

void _find_maze_dimensions(FILE * fp, int * num_rows, int * num_cols) 
{
	fseek(fp, 0, SEEK_SET);
	*num_rows = *num_cols = 0;
	while( fgetc(fp) != '\n' )//calculates number of columns
	{
		(*num_cols)++;
	}
	fseek(fp, 0, SEEK_SET);
	while( !feof(fp) ) //calculates number of rows
	{
		char ch = fgetc(fp);
		if(ch == '\n')
		{
			(*num_rows)++;
		}
	}
}
