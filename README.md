# Maze-Solving-and-Manipulation

General Description: This repository contains code for solving a maze of any dimensions using a recursive technique. The solution generated is always the shortest path. Other maze and file manipulation code is also included for performing basic operations with the maze generated using maze_generator.

# Components of this repository

1) maze_generator: This is an executable (originally written in C) that generates a file containing a maze of dimensions specified by user. To run this, use the format given below in the commandline. This will generate a maze of dimensions (2a+1) x (2b+1) with the walls made of characters depending on the last argument.

       maze_generator [+ve int value (a)] [+ve int value (b)] [ints 1-8 or single char] > [destination filename]
       
       eg.
       maze_generator 7 7 X > maze_sample_15x15.txt

2) File Operation Code: This code performs basic maze file manupilations using C file handling operations. This segment refers to files: file_operations.h, file_operations.c and use_file_operations.c. After compiling the two .c files to a single executable, two arguments must be passed to run the executable. The format is as follows:

       <executable filename> [maze filename] [destination filename for single line output]
       
       eg.
       ./file_operations maze_sample_15x15.txt maze_sample_directions.txt

3) Maze Manipulation Code: This code reads maze from a file containing a maze and stores it in a struct. It performs various operations such as generating a valid widened maze and valid taller maze using the maze read from the file. It is also capible of writing the a maze to a file. After compiling the two .c files to a single executable, the executable can be run without any additional arguments.

4) Maze Solver Code: This code is capible of solving any given maze generated using maze_generator and generating a file which contains a maze with the shortest path marked. This segment refers to files: maze_manipulation.h, maze_manipulation.c and use_maze_manipulation.c. After compiling the two .c files to a single executable, multiple arguments must be passed to run the executable. The format is as follows:


       //Solving the maze and storing directions in a file
       <executable filename> -m [maze filename] [destination filename for path directions] [start row] [start col] [end row] [end col]
      
       eg.
       ./maze_manipluation -m maze_sample_15x15.txt directions.txt 0 7 14 7
       
       //Storing a maze with the solution marked  in a new file
       <executable filename> -m [maze filename] [path directions filename] [destination filename with solution marked maze] [start row] [start col] [end row] [end col]
      
       eg.
       ./maze_manipluation -s maze_sample_15x15.txt directions.txt sample_maze_solution.txt 0 7 14 7
