# Maze-Solving-and-Manipulation

General Description: This repository contains code for solving a maze of any dimensions using a recursive technique. The solution generated is always the shortest path. Other maze and file manipulation code is also included for performing basic operations with the maze generated using maze_generator.

# Components of this repository

1) maze_generator: This is an executable (originally written in C) that generates a file containing a maze of dimensions specified by user. To run this, use the format given below in the commandline. This will generate a maze of dimensions (2a+1) x (2b+1) with the walls made of characters depending on the last argument.

       maze_generator [positive integer value (a)] [positive integer value (b)] [integers 1 to 8 or character] > [destination filename]

2) File operation codes: This code helps perform basic maze file manupilations using C file handling operations. This segment refers to files: file_operations.h, file_operations.c and use_file_operations.c.

3) 
