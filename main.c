/*
* CSE 430 Assignment 2 - 25 September 2014
* Matrix Multiplication - Multithreading
*/

//===========Included Headers==========//
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <pthread.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

//=========Constants, Global Variables, and Forward Declarations=========//

int matSize(char*);
void *doyourpart(void*);
int *parseMatrix(char*);
void printMatrix();

int **mat1, **mat2, **rMat;
int N, TT;

//===========Begin Main Method============//
int main(int argc, char *argv[])
{
	double executionTime;
	struct timeval start, end; //used for timing
	gettimeofday(&start, NULL);
	if (argc == 5) {
		TT = atoi(argv[4]);
	}
	else {
		TT = 256;
	}
	//========Variable Declaration========//
	FILE *fr1, *fr2, *fw;
	char line[32000];

	//==========File Reading==========// 
	fr1 = fopen(argv[1], "r");
	fr2 = fopen(argv[2], "r");
	if (fr1 == NULL || fr2 == NULL) //If something goes wrong
	{
		printf("Error: Cannot open one of the input files.");
		exit(1);
	}

	//Read the first line of the input file and count the number of columns
	//===MAT 1===//
	fgets(line, 32000, fr1); //read line
	N = matSize(line);
	mat1 = (int **)malloc(sizeof(int *)*N);
	for (int i = 0; i < N; i++)
	{
		mat1[i] = parseMatrix(line); //Set each row to the array
		fgets(line, 32000, fr1);
	}
	fclose(fr1);

	//===MAT 2===//
	// Copy mat1
	mat2 = (int **)malloc(sizeof(int *)*N);
	for (int i = 0; i < N; i++)
	{
		mat2[i] = (int *)malloc(sizeof(int)*N);
		for (int j = 0; j < N; j++)
		{
			mat2[i][j] = mat1[i][j];
		}
	}

	//===Result Matrix===//
	rMat = (int **)malloc(sizeof(int *)*N);
	for (int k = 0; k < N; k++)
		rMat[k] = (int *)malloc(sizeof(int)*N);

	//Initialize threading
	int parts[TT];
	pthread_t tid[TT];
	pthread_attr_t pt_attribs;

	for (int i = 0; i < TT; i++)
	{
		parts[i] = i;
		pthread_attr_init(&pt_attribs);
		pthread_create(&(tid[i]), &pt_attribs, doyourpart, &(parts[i]));
	}

	//Wait for threads to finish
	for (int i = 0; i < TT; i++)
	{
		pthread_join(tid[i], NULL);
	}

	//Print to console
	if (argc == 4)
		printMatrix();
	else  //Print to file
	{
		fw = fopen(argv[3], "w");
		if (fw == NULL)
		{
			printf("Error: cannot open output file.\n");
			exit(1);
		}

		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				fprintf(fw, "%d ", rMat[i][j]);
			}
			fprintf(fw, "\n");
		}
		fclose(fw);
	}
	//Execution Time
	gettimeofday(&end, NULL);
	executionTime = ((end.tv_sec + end.tv_usec / 1000000.0) - (start.tv_sec + start.tv_usec / 1000000.0));
	printf("Execution Time: %lf seconds\n", executionTime);
	return 0;
}

//===================Begin Helper Methods===================//
//Each thread completes this portion of the code to multiply its part
void *doyourpart(void *param)
{
	//
	int factor = N / (int)sqrt(TT);
	int col = *((int *)param) % (int)sqrt(TT);
	int row = *((int *)param) / (int)sqrt(TT);

	int col_lowerBound = col * factor;
	int col_upperBound = (col + 1) * factor;
	int row_lowerBound = row * factor;
	int row_upperBound = (row + 1) * factor;

	for (int i = row_lowerBound; i < row_upperBound; i++) { //traverse rows of matrix 1
		for (int j = col_lowerBound; j < col_upperBound; j++) { //traverse columns of 1, rows of 2
			int sum = 0;
			for (int k = 0; k < N; k++) { //traverse columns of 2
				sum += mat1[i][k] * mat2[k][j];
			}
			rMat[i][j] = sum;
		}
	}

	pthread_exit(0);
}

//The following function will count the number of elements per line
//and return the number of rows and columns for the matrix
int matSize(char *line)
{
	int count = 0;
	if (sizeof(line) > 0) {
		int i = 0;
		while (line[i] != '\n') {
			if (line[i] == ' ')
				count++;
			i++;
		}
		count++;
	}
	return count;
}


//This method will take the line and parses it into an array of integers
int* parseMatrix(char* line) {
	int* result = (int *)malloc(sizeof(int)*N); //allocate memory to new 1-D array
	char *delimiter = " ";
	char *number = NULL;
	number = strtok(line, delimiter);  //Points to delimiter within char*
	int i = 0;
	while (number != NULL && i < N) {
		int x = atoi(number);  //convert to integer
		result[i] = x;  //store in new array
		number = strtok(NULL, delimiter); //get to next pointer
		i++;
	}
	return result;
}

//Prints matrix to the console
void printMatrix() {
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%d ", rMat[i][j]);
		}
		printf("\n");
	}
}
