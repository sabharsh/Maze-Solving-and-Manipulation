#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze_solver.h"

int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file);

int main(int argc, char* argv[]) 
{
	if (argc < 2) 
	{
		return EXIT_FAILURE;
	}
	if (strcmp("-s", argv[1]) == 0) 
	{
		if (argc != 9)
		{
			return EXIT_FAILURE;
		}
		char* e_start_r;
		int     start_r = strtol(argv[5], &e_start_r, 10);
		char* e_start_c;
		int     start_c = strtol(argv[6], &e_start_c, 10);
		char* e_end_r;
		int     end_r = strtol(argv[7], &e_end_r, 10);
		char* e_end_c;
		int     end_c = strtol(argv[8], &e_end_c, 10);

		/*printf("\ne_start_r:%s\nstart_r: %d\n", e_start_r, start_r);
		printf("e_start_c:%s\nstart_c: %d\n", e_start_c, start_c);
		printf("e_end_r:%s\nend_r: %d\n", e_end_r, end_r);
		printf("e_end_c:%s\nend_c: %d\n", e_end_c, end_c);*/
		if(e_start_r[0]!='\0' || e_start_c[0]!='\0' || e_end_r[0]!='\0' || e_end_c[0]!='\0')
		{
			return EXIT_FAILURE;
		}
		//printf("\nstart_r: %d\nstart_c: %d\nend_r: %d\nend_c: %d\n", start_r, start_c, end_r, end_c);
		Coord source = {
			.row = start_r,
			.col = start_c
		};
		Coord destination = {
			.row = end_r,
			.col = end_c
		};
		int step_count = simulate_movement(argv[2], argv[3], argv[4], source, destination);
		printf("%d\n", step_count); 
	}
	else if (strcmp("-m", argv[1]) == 0) 
	{
		if (argc != 8)
		{
			return EXIT_FAILURE;
		}
		char* e_start_r;
		int     start_r = strtol(argv[4], &e_start_r, 10);
		char* e_start_c;
		int     start_c = strtol(argv[5], &e_start_c, 10);
		char* e_end_r;
		int     end_r = strtol(argv[6], &e_end_r, 10);
		char* e_end_c;
		int     end_c = strtol(argv[7], &e_end_c, 10);
		if(e_start_r[0]!='\0' || e_start_c[0]!='\0' || e_end_r[0]!='\0' || e_end_c[0]!='\0')
		{
			return EXIT_FAILURE;
		}
		Coord source = {
			.row = start_r,
			.col = start_c
		};
		Coord destination = {
			.row = end_r,
			.col = end_c
		};
		int step_count = dfs_shortest_path_directions(argv[2], argv[3], source, destination);
		printf("%d\n", step_count); 
	}
	else
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
