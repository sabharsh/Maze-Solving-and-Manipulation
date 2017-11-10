#include <stdio.h>
#include <stdlib.h>
#include "file_operations.h"

void print_maze(FILE * fp);
void print_maze_using_pos(FILE * fp, int r, int c);

/*

Arguments for main(...):
argv[1]: name of file containing maze
argv[2]: name of file to write the maze in a single line

*/

int main(int argc, char ** argv) 
{
	FILE * fp = fopen(argv[1], "r");

	int num_rows, num_cols;
	find_maze_dimensions(fp, &num_rows, &num_cols);
	printf("find_maze_dimensions:   %dx%d\n", num_rows, num_cols);
	
	printf("find_opening_location:  %d\n", find_opening_location(fp));

	printf("count_path_locations:   %d\n", count_path_locations(fp));

	printf("get_location_type(3,4): %c\n", get_location_type(fp, 3, 4));

	printf("represent_maze_in_one_line: %d\n", represent_maze_in_one_line(argv[2], fp));

	print_maze(fp);

	print_maze_using_pos(fp, num_rows, num_cols);

	fclose(fp);
}

void print_maze(FILE	* fp)
{
	rewind(fp);
	char ch = '\0';
	printf("\n");
	while( (ch=getc(fp)) != EOF )
	{
		printf("%c",ch);
	}
	printf("\n");
}

void print_maze_using_pos(FILE * fp, int r, int c)
{
	for(int i=0; i<r; i++)
	{
		for(int j=0; j<c; j++)
		{
			printf("%c",get_location_type(fp,i,j));
		}
		printf("\n");
	}
}
