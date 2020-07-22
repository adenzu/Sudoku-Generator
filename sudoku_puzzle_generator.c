#include <stdio.h>
#include <stdlib.h>
#include "sudoku_puzzle_generator.h"

/*DEVELOPMENT PURPOSES FUNCTIONS*/
void print_array(int * arr, int len){
	for(int i = 0; i < len; i++) printf("%d ", arr[i]);
	printf("\n");
}

void print_sudoku_field(int width, int height, int ** sudoku_field){

	int i, j;
	int size = width * height;

	for(i = 0; i < size; i++){
		
		if(i && !(i % height)) printf("\n");

		for(j = 0; j < size; j++){

			if(j && !(j % width)) printf("  ");
			printf("%d ", sudoku_field[i][j]);
		}
		
		printf("\n");
	}
	
	printf("\n");
}

/*ACTUAL FUNCTIONS*/
int random_range(int l, int u){
	return rand() % (u-l) + l;
}

int * range_array(int l, int u){

	int i, len = u-l;
	int * new_int_array = (int *) calloc(len, sizeof(int));

	for(i = 0; i < len; i++) new_int_array[i] = l++;

	return new_int_array;
}

int * n_times_array(int num, int n){

	int i;
	int * new_int_array = (int *) calloc(n, sizeof(int));

	for(i = 0; i < n; i++) new_int_array[i] = num;

	return new_int_array;
}

int len_without(int * arr, int len, int x){

	int true_len = len;

	while(len--){
		if(arr[len] == x) true_len--;
	}

	return true_len;
}

int random_choice_index_without(int * arr, int len, int x){

	int i;

	int true_len = len_without(arr, len, x);

	if(true_len){
		
		int true_index = random_range(0, true_len);

		for(i = 0; 1 + true_index; i++){
			if(arr[i] != x) true_index--;
		}

		i--;
	}
	else i = -1;
	
	return i;
}

int ** create_sudoku_field(int width, int height){

	int i;
	int size = width * height;

	int ** new_sudoku_field = (int **) calloc(size, sizeof(int *));

	for(i = 0; i < size; i++) new_sudoku_field[i] = n_times_array(0, size);

	return new_sudoku_field;
}

int *** create_check_array(int width, int height){

	int i, j;
	int size = width * height;

	int *** new_check_array = (int ***) calloc(size, sizeof(int **));

	for(i = 0; i < size; i++){

		new_check_array[i] = (int **) calloc(size, sizeof(int *));

		for(j = 0; j < size; j++) new_check_array[i][j] = n_times_array(1, size);
	}

	return new_check_array;
}

void remove_possible_squares(int * arr, int len){
	while(len--) arr[len] = 0;
}

void remove_same_section(int square_index, int width, int height, int ** arr){

	int size = width * height;

	while(size--) arr[size][square_index] = 0;
}

void remove_other_sections(int section, int value, int square, int width, int height, int *** arr){

	int i, j;

	int size = width * height;

	int curr_section;

	int s_x = section % width;
	int s_y = section / width;

	int v_x = square % width;
	int v_y = square / width;

	int * remove_vert = (int *) calloc(height, sizeof(int));
	int * remove_horz = (int *) calloc(width, sizeof(int));

	for(i = 0; i < height; i++) remove_vert[i] = i * width + v_x;
	for(i = 0; i < width; i++)  remove_horz[i] = i + v_y * width;

	for(i = 0; i < height; i++){

		curr_section = i * width + s_x;

		if(curr_section != section){

			for(j = 0; j < height; j++) arr[curr_section][value][remove_vert[j]] = 0;
		}
	}

	for(i = 0; i < width; i++){

		curr_section = i + s_y * width;
		
		if(curr_section != section){

			for(j = 0; j < width; j++) arr[curr_section][value][remove_horz[j]] = 0;
		}
	}
}

int sum_array(int * arr, int len){

	int result = 0;

	while(len--) result += arr[len];

	return result;
}

int random_value(int ** arr, int len){

	int i;
	int result;

	int * possible_values = n_times_array(0, len);

	for(i = 0; i < len; i++){
		if(sum_array(arr[i], len)) possible_values[i] = 1;
	}

	return random_choice_index_without(possible_values, len, 0);
}

void update_check_array(int * section_situations, int width, int height, int *** arr){

	int section, value;
	int found = 0;
	int size = width * height;
	int square;

	for(section = 0; section < size && !found; section++){
		for(value = 0; value < size; value++){
			if(sum_array(arr[section][value], size) == 1){
				found = 1;
				break;
			}
		}
	}

	if(found){

		square = random_choice_index_without(arr[--section][value], size, 0);

		remove_possible_squares(arr[section][value], size);
		remove_same_section(square, width, height, arr[section]);
		remove_other_sections(section, value, square, width, height, arr);

		section_situations[section]--;

		update_check_array(section_situations, width, height, arr);
	}
}

void create_sudoku_puzzle(int width, int height){

	int size = width * height;

	int x, y;
	int section, value, square;

	int ** sudoku_field = create_sudoku_field(width, height);
	int *** check_array = create_check_array(width, height);

	int * section_possible_value_count = n_times_array(size, size);

	while((section = random_choice_index_without(section_possible_value_count, size, 0)) != -1){

		value  = random_value(check_array[section], size);
		square = random_choice_index_without(check_array[section][value], size, 0);

		x = width * (section % width) + square % width;
		y = height * (section / width) + square / width;

		sudoku_field[y][x] = value + 1;

		remove_possible_squares(check_array[section][value], size);
		remove_same_section(square, width, height, check_array[section]);
		remove_other_sections(section, value, square, width, height, check_array);

		section_possible_value_count[section]--;

		update_check_array(section_possible_value_count, width, height, check_array);
	}
	print_sudoku_field(width, height, sudoku_field);
}