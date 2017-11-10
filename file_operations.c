#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "file_operations.h"

void find_maze_dimensions(FILE * fp, int * num_rows, int * num_cols) 
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

int find_opening_location(FILE * fp) 
{
	fseek(fp, 0, SEEK_SET);
	int pos = 0;
	while( fgetc(fp) != PATH )
	{
		pos++;
	}
	return pos;
}

int count_path_locations(FILE * fp) 
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

char get_location_type(FILE * fp, int row, int col) 
{
	fseek(fp, 0, SEEK_SET);
	int row_pos=0;
	int col_pos=0;
	while( row_pos!=row || col_pos!=col)//increments position in maze and takes fgetc to required position
	{
		char ch=fgetc(fp);
		if(ch == '\n')
		{
			row_pos++;
			col_pos=0;
		}
		else
		{
			col_pos++;
		}
	}
	return fgetc(fp);
}
 
int represent_maze_in_one_line(char * filename, FILE * fp) 
{
	fseek(fp, 0, SEEK_SET);
	FILE * one_line_file = fopen(filename,"w");
	int count=0;
	while( true )
	{
		char ch = fgetc(fp);
		if( feof(fp) )
		{
			break;
		}
		else if(ch != '\n')//writes all chars except '\n' to required file
		{
			fputc(ch, one_line_file);
			count++;
		}
	}
	fclose(one_line_file);
	return count;
}
