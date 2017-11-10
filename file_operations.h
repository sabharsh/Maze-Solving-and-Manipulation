#ifndef MAZE_H
#define MAZE_H 

#define WALL 'X'
#define PATH ' '
#define MAZE_WRITE_FAILURE -1


#include <stdio.h>

void find_maze_dimensions(FILE* fp, int* num_rows, int* a_num_cols);

int find_opening_location(FILE* fp);

int count_path_locations(FILE* fp);

char get_location_type(FILE* fp, int row, int col);

int represent_maze_in_one_line(char* filename, FILE* fp);

#endif
