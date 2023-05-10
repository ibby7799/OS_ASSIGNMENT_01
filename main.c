/**
 * @defgroup   MAIN main
 *
 * @brief      This file implements main. Please Comment you code
 *
 * @author     k213093 Muhammad Ibrahim
 * @date       2023
 */

#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define row 5
#define col 10
#ifndef shared_memory
#define shared_memory

// attach memory block
char * attach_memory_block(char *filename, int size);
// detach memory block
bool detach_memory_block(char *block);
// destroy memory block
bool destroy_memory_block(char *filename);

#define block_size 4096
#define FILENAME "writeshmem.c"
#define IPC_RESULT_ERROR (-1)

int cur_grid[row][col];
int next_grid[row][col];

// Initialize the grid with random values
void initialize() 
{
    int i, j;
    for(i = 0; i < row; i++) 
	{
        for (j = 0; j < col; j++) 
		{
            cur_grid[i][j] = rand() % 2; // store 0 or 1 at index by random function
		} // Any number when its divided by 2 its remainder will be zero or one
    }
}

// Display the current grid state
void display() 
{
    int i, j;
    for (i = 0; i < row; i++)
	{
        for (j = 0; j < col; j++)
		{
            printf("%d",cur_grid[i][j]);//printing grid index by index
        }
        printf("\n");
    }
}

//Update the grid according to the rules of the game
void update() 
{
    int i, j, x, y, count;// important variable to initialize

    for (i = 0; i < row; i++)
	{//loop for rows
        for (j = 0; j < col; j++) 
		{//loop for columns
		// iterate over each element
            count = 0;//initialize count with zero

            // Counting the number of live neighbors(indexes)
            for (x = i-1; x <= i+1; x++)// checks row adjacent elements
			 {
                for (y = j-1; y <= j+1; y++) //checks column adjacet elements
				{
                    if (x >= 0 && x < row && y >= 0 && y < col && !(x == i && y == j)) 
					{//if x and y are >=0 and < row and column respectively
					 //and x equals to current row index
					 //y equals current column index
					 // add the grid index value according to x and y in  count
					 // if value is zero count will not increment buf if it is 1 it will increment
                        count += cur_grid[x][y];
                    }
                }
            }

            // Apply the rules of the game
            //now checking if alive neighbors are less than 2 or greater then 3 
            //element will survivie other wise it will die
            if (cur_grid[i][j] == 1) 
			{
                if (count < 2 || count > 3)
				{
                    next_grid[i][j] = 0;
                } 
				else 
				{
                    next_grid[i][j] = 1;
                }
            } 
			else 
			{
                if (count == 3)
				{
                    next_grid[i][j] = 1;
                } 
				else 
				{
                    next_grid[i][j] = 0;
                }
            }
        }
    }

    //Copying the next temporary grid to the current or main grid
    for (i = 0; i < row; i++)
	{
        for (j = 0; j < col; j++) 
		{
            cur_grid[i][j] = next_grid[i][j];
        }
    }
}

static int get_shared_block(char *filename, int size)
{
    // Request a key
    // key is linked to filename so the programs can access it 
    key_t key;
    key = ftok(filename,0);
    if(key == IPC_RESULT_ERROR)
    {
    	return IPC_RESULT_ERROR;
    }
    // create shared block
    return shmget(key, size, 0644 | IPC_CREATE);
}
    
char *attach_memory_block(char *filename, int size)
{
    int shared_block_id = get_shared_block(filename, size);
    char *result;
    	
    if(shared_block_id == IPC_RESULT_ERROR)
    {
    	return NULL;
    }
    	
    result = shmat(shared_block_id, NULL, 0);
    if(result == (char *)IPC_RESULT_ERROR)
    {
    	return NULL;
    }
    return result;
}
    
bool detach_memory_block(char *block)
{
    return (shmdt(block) != IPC_RESULT_ERROR)
}
    
bool destroy_memory_block(char *filename)
{
    int shared_block_id = get_shared_block(filename, 0);
    	
    if(shared_block_id == IPC_RESULT_ERROR)
    {
    	return NULL;
    }
    return (shmctl(shared_block_id, IPC_RMID, NULL) != IPC_RESULT_ERROR);
}
    


/**
 * @brief      { function_description }
 *
 * @param[in]  argc  The count of arguments
 * @param      argv  The arguments array
 *
 * @return     { description_of_the_return_value }
 */
int main(int argc, char const *argv[])
{
        int fd[2];
    int pid = fork();
    if(pid == -1)
    {
    	return 2;
    }	
    
    display();
    if(pid==0)
    {
    	initialize();
    	get_shared_block(FILENAME,block_size);
    	close(fd[0]);	
    	write(fd[1], cur_grid[row][col], sizeof(cur_grid));
    	*attach_memory_block(FILENAME, sizeof(cur_grid))
    	close(fd[0]);
    	int pid1 = fork();
    	if(pid1==0)
    	{
    		int x=2
   		while (x==0)
		{
        	system("clear"); // Clear the console
        	update();
        	display();
        	usleep(300000); // Sleep for 100 milliseconds
        	x = x-1;
        	}
    		get_shared_block(FILENAME,block_size);
    		close(fd[0]);	
    		write(fd[1], cur_grid[row][col], sizeof(cur_grid));
    		close(fd[0]);
	}
	int pid2 = fork();
    	if(pid2==0)
    	{
    		int x=2
   		while (x==0)
		{
        	system("clear"); // Clear the console
        	update();
        	display();
        	usleep(300000); // Sleep for 100 milliseconds
        	x = x-1;
        	}
    		get_shared_block(FILENAME,block_size);
    		close(fd[0]);	
    		write(fd[1], cur_grid[row][col], sizeof(cur_grid));
    		close(fd[0]);
	}
	int pid3 = fork();
    	if(pid3==0)
    	{
    		int x=1
   		while (x==0)
		{
        	system("clear"); // Clear the console
        	update();
        	display();
        	usleep(300000); // Sleep for 100 milliseconds
        	x = x-1;
        	}
    		get_shared_block(FILENAME,block_size);
    		close(fd[0]);	
    		write(fd[1], cur_grid[row][col], sizeof(cur_grid));
    		close(fd[0]);
	}
    }
    else
    {
    	//parent
    	close(fd[1]);
    	read(fd[0],next_grid[row][col], sizeof(next_grid));
    	display();
    	close(fd[0]);
    	wait(NULL);
    }
    
    exit(0);

    // It is left up to you how you use shared memory and multiple processes 
    // to solve the conway problem
    return 0;
}
