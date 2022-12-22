#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N1 666 //Количество строк матрицы A
#define N2 666 //Количество столбцов матрицы A и количество строк матрицы B
#define N3 666 //Количество столбцов матрицы B

void fillMatrix(); //Заполнить матрицы, которые будут перемножаться
void printMatrix(); //Вывести матрицы

int rank; //Ранг процессов
int size; //Количество процессов
int i, j, k; //Вспомогательные переменные
double matrixA[N1][N2]; //Объявление матрицы A
double matrixB[N2][N3]; //Объявление матрицы B
double matrixRes[N1][N3]; //Объявление матрицы перемножения 
double start_time; //Начальное время
double end_time; //Время конца

int main(int argc, char* argv[])
{
	fillMatrix();
	for (int t = 1; t < omp_get_num_procs() + 1; t++)
	{
		//Устанавливаем число потоков
		omp_set_num_threads(t);
		#pragma omp parallel shared(matrixA, matrixB, matrixRes) private(i, j, k)
		{
			#pragma omp for shedule (static)
			start_time = omp_get_wtime();
			for (i = 0; i < N1; i++) {
				for (j = 0; j < N2; j++) {
					for (k = 0; k < N3; k++) {
						matrixRes[i][j] = (matrixA[i][k] * matrixB[k][j]);
					}
				}
			}
			end_time = omp_get_wtime();
			//printMatrix();
			printf("\nTime = %f\n", end_time - start_time);
		}
	}
	return 0;
}

void fillMatrix()
{
	srand(time(NULL));
	for (i = 0; i < N1; i++) {
		for (j = 0; j < N2; j++) {
			matrixA[i][j] = rand() / 10.0;
		}
	}
	for (i = 0; i < N2; i++) {
		for (j = 0; j < N3; j++) {
			matrixB[i][j] = rand() / 10.0;
		}
	}
}

void printMatrix()
{
	for (i = 0; i < N1; i++) {
		printf("\n");
		for (j = 0; j < N2; j++)
			printf("%8.2f  ", matrixA[i][j]);
	}
	printf("\n\n\n");
	for (i = 0; i < N2; i++) {
		printf("\n");
		for (j = 0; j < N3; j++)
			printf("%8.2f  ", matrixB[i][j]);
	}
	printf("\n\n\n");
	for (i = 0; i < N1; i++) {
		printf("\n");
		for (j = 0; j < N3; j++)
			printf("%8.2f  ", matrixRes[i][j]);
	}
	printf("\n\n");
}