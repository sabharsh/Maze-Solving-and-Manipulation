#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "maze_solver.h"

Maze* malloc_maze(int n_row, int n_col);
void free_maze(Maze* maze);
Maze* read_maze(FILE* fp);
bool write_maze(const char* filename, const Maze* maze);
int _pathfinder_helper(Maze *maze, int curr, int curc, int endr, int endc, int count, char* path, char* shortest_path);
void _find_maze_dimensions(FILE * fp, int * n_row, int * n_col); 
int _count_path_locations(FILE * fp);
bool _write_path(FILE* fp, char* path);
void _print(Maze* maze);

bool _is_path(Maze *maze, int row, int col)
{
   if ((row >= 0) && (row < maze->n_row)) 
   {
      if ((col >= 0) && (col < maze->n_col)) 
	  {
         return maze->maze_array[row][col] == PATH;
      }
   }
   return false;
}

int dfs_shortest_path_directions(char *maze_file, char *directions_file, Coord source, Coord destination)
{
	FILE *mfptr = fopen(maze_file, "r");                             //OPENING MAZE FILE
	if (mfptr == NULL) 
	{
		return -1;
	}
	Maze *maze = read_maze(mfptr); //reading maze from maze file
	int num_path_locations = _count_path_locations(mfptr);
	fclose(mfptr);                                                   //CLOSING MAZE FILE
	if ( maze == NULL || !_is_path(maze, source.row, source.col ) || !_is_path(maze, destination.row, destination.col) ) 
	{// terminating if maze is NULL or start or end locations are invalid.
		free_maze(maze);
		return -1;
	}
	FILE *dfptr = fopen(directions_file, "w");                       //OPENING DIRECTIONS FILE
	if (dfptr == NULL) 
	{
		free_maze(maze);
		return -1;
	}
	char* path = malloc( sizeof(*path) * num_path_locations );
	char* shortest_path = malloc( sizeof(*path) * num_path_locations );
	int pos = 0;
	while(pos < num_path_locations)
	{
		path[pos] = '\0';
		shortest_path[pos] = '.';
		pos++;
	}
	shortest_path[pos-1] = '\0';
	int steps = _pathfinder_helper(maze, source.row, source.col, destination.row, destination.col, 0, path, shortest_path);
	//printf("shortest_path: %s\n", shortest_path);
	if(!_write_path(dfptr, shortest_path))
	{
		return -1;
	}
	fclose(dfptr);                                                   //CLOSING DIRECTIONS FILE
	free(path);
	free(shortest_path);

	free_maze(maze);
	return steps;
}

int _pathfinder_helper(Maze *maze, int curr, int curc, int endr, int endc, int count, char* path, char* shortest_path)
{
	maze->maze_array[curr][curc] = VISITED;
	if ((curr == endr) && (curc == endc)) 
	{ // reach the destination 
		int shortest_length = 0;
		while(shortest_path[shortest_length] != '\0')
		{
			shortest_length++;
		}
		/*printf("\nshortest_path:   %s\n", shortest_path);
		printf("shortest_length: %d\n", shortest_length);
		printf("path:            %s\n", path);
		printf("count:           %d\n", count);
		_print(maze);*/
		if(shortest_length > count)
		{
			int pos = 0;
			while(shortest_path[pos] != '\0')
			{
				shortest_path[pos] = '\0';
				pos++;
			}
			pos = 0;
			while(path[pos] != '\0')
			{
				shortest_path[pos] = path[pos];
				pos++;
			}
			
			maze->maze_array[curr][curc] = PATH;
			return count;
		}
		maze->maze_array[curr][curc] = PATH;
		return -1;// if the path found isn't shorter than the previous one
	}
	
	int found[4] = {-1,-1,-1,-1}; //0->N, 1->S, 2->E, 3->W
	if (_is_path(maze, curr-1, curc)) 
	{
		path[count] = 'N';
		found[0] = _pathfinder_helper(maze, curr-1, curc, endr, endc, count+1, path, shortest_path);
	}
	if (_is_path(maze, curr+1, curc)) 
	{
		path[count] = 'S';
		found[1] = _pathfinder_helper(maze, curr+1, curc, endr, endc, count+1, path, shortest_path);
	}
	if (_is_path(maze, curr, curc+1)) 
	{
		path[count] = 'E';
		found[2] = _pathfinder_helper(maze, curr, curc+1, endr, endc, count+1, path, shortest_path);
	}
	if (_is_path(maze, curr, curc-1)) 
	{
		path[count] = 'W';
		found[3] = _pathfinder_helper(maze, curr, curc-1, endr, endc, count+1, path, shortest_path);
	}
	path[count] = '\0';
	int shortest_found = -1;
	for(int i=0; i<4; i++)
	{
		if(found[i] >= 0)
		{
			shortest_found = found[i];
		}
	}
	maze->maze_array[curr][curc] = PATH;
	return shortest_found;
}

int simulate_movement(char *maze_file, char *directions_file, char *visited_file, Coord source, Coord destination)
{
	FILE *mfptr = fopen(maze_file, "r");                             //OPENING MAZE FILE
	if (mfptr == NULL) 
	{
		//printf("maze file didnt open\n");
		return -1;
	}
	Maze *maze = read_maze(mfptr); //reading maze from maze file
	fclose(mfptr);                                                   //CLOSING MAZE FILE
	if ( maze == NULL || !_is_path(maze, source.row, source.col ) || !_is_path(maze, destination.row, destination.col) ) 
	{	// terminating if maze is NULL or start or end locations are invalid.
		//printf("maze is NULL or start or end locations are invalid\n");
		free_maze(maze);
		return -1;
	}
	FILE *dfptr = fopen(directions_file, "r");                       //OPENING DIRECTIONS FILE
	if (dfptr == NULL) 
	{
		//printf("directions file didnt open\n");
		free_maze(maze);
		return -1;
	}
	Coord current = {
		.row = source.row,
		.col = source.col
	};
	maze->maze_array[current.row][current.col] = VISITED;
	int movements = 1;
	while(true)
	{
		char direction = fgetc(dfptr);
		if(direction==EOF)
		{
			break;
		}
		else if(direction == 'N')
		{
			current.row--;
		}
		else if(direction == 'S')
		{
			current.row++;
		}
		else if(direction == 'E')
		{
			current.col++;
		}
		else if(direction == 'W')
		{
			current.col--;
		}
		else
		{
			//printf("invalid direction\n");
			fclose(dfptr);
			free_maze(maze);
			return -1;
		}
		if(_is_path(maze, current.row, current.col ))
		{
			maze->maze_array[current.row][current.col] = VISITED;
			movements++;
		}
		else
		{
			//printf("direction to invalid path\n");
			fclose(dfptr);
			free_maze(maze);
			return -1;
		}
	}
	fclose(dfptr);                                                   //CLOSING DIRECTIONS FILE
	if(!write_maze(visited_file,maze))
	{
		//printf("failed to write to visited file\n");
		free_maze(maze);
		return -1;
	}
	free_maze(maze);
	if(current.row == destination.row && current.col == destination.col)
	{
		return movements;
	}
	//printf("didn't reach destination\n");
	return -1;
}

Maze* malloc_maze(int n_row, int n_col)
{
	Maze* a_maze = malloc( sizeof(a_maze -> n_row) +  sizeof(a_maze -> n_col) + sizeof(a_maze -> maze_array) );//mallocs for struct
	if(a_maze == NULL)
	{
		return NULL;
	}
	a_maze -> n_row = n_row;
	a_maze -> n_col = n_col;
	a_maze -> maze_array    = malloc( sizeof(*(a_maze -> maze_array)) * n_row); //mallocs for row array (which stores the address of the column arrays)
	if(a_maze -> maze_array == NULL)
	{
		free( a_maze );
		return NULL;
	}
	for(int i=0; i<n_row; i++)
	{
		a_maze -> maze_array[i] = malloc( sizeof( *(a_maze -> maze_array[0]) ) * n_col );//mallocs for each column
		if(a_maze -> maze_array[i] == NULL)//frees everything in case of malloc error
		{
			for(int j=0; j<i; j++)
			{
				free( a_maze -> maze_array[j] );
			}
			free( a_maze -> maze_array);
			free( a_maze );
			return NULL;
		}
	}
	return a_maze;
}

void free_maze(Maze* maze)
{
	if(maze == NULL)
	{
		return;
	}
	for(int i=0; i<(maze -> n_row); i++)//frees each column
	{
		free( maze -> maze_array[i] );
	}
	free(maze -> maze_array);//frees the row array (which stores the addresses of the first char of the column arrays)
	free(maze);//frees the struct
}

Maze* read_maze(FILE* fp)
{
	int n_row = 0;
	int n_col = 0;
	_find_maze_dimensions(fp, &n_row, &n_col); //calculating maze dimensions using helper function
	Maze* maze = malloc_maze(n_row, n_col);
	if(maze == NULL)
	{
		return NULL;
	}
	fseek(fp, 0, SEEK_SET);
	for(int i=0; i<n_row; i++)
	{
		for(int j=0; j<n_col; j++)
		{
			char ch = fgetc(fp);
			if(ch == '\n')
			{
				ch = fgetc(fp);
			}
			maze -> maze_array[i][j] = ch;
		}
	}
	return maze;
}

bool write_maze(const char* filename, const Maze* maze)
{
	FILE * fp = fopen(filename, "w");
	for(int i=0; i < maze -> n_row; i++)
	{
		for(int j=0; j < maze -> n_col; j++)
		{
			char ch = fputc(maze -> maze_array[i][j], fp);
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

void _find_maze_dimensions(FILE * fp, int * n_row, int * n_col) 
{
	fseek(fp, 0, SEEK_SET);
	*n_row = *n_col = 0;
	while( fgetc(fp) != '\n' )//calculates number of columns
	{
		(*n_col)++;
	}
	fseek(fp, 0, SEEK_SET);
	while( !feof(fp) ) //calculates number of rows
	{
		char ch = fgetc(fp);
		if(ch == '\n')
		{
			(*n_row)++;
		}
	}
}

int _count_path_locations(FILE * fp) 
{
	fseek(fp, 0, SEEK_SET);
	int count=0;
	while( !feof(fp) )
	{
		char ch = fgetc(fp);
		if(ch == PATH)
		{
			count++;
		}
	}
	return count;
}

bool _write_path(FILE* fp, char* path)
{
	int length=0;
	while(path[length] != '\0')
	{
		length++;
	}
	int pos=0;
	while(pos < length)
	{
		char ch = fputc(path[pos], fp);
		if(ch == EOF)
		{
			fclose(fp);
			return false;
		}
		pos++;
	}
	return true;
}

void _print(Maze* maze)
{
	//printf("n_rows: %d\nn_cols: %d\n", maze -> n_row, maze -> n_col);
	for(int i=0; i < maze->n_row; i++)
	{
		for(int j=0; j < maze->n_col; j++)
		{
			fputc(maze -> maze_array[i][j], stdout);
		}
		fputc('\n', stdout);
	}
}
