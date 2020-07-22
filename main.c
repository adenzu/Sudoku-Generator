#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sudoku_puzzle_generator.h"

int main(){

	int w, h;
	srand(time(0));

	printf("enter width and height:\n");
	scanf("%d %d", &w, &h);
	printf("\n");
	create_sudoku_puzzle(w, h);

	return 0;
}