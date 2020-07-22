#ifndef SOME_PROT_IDK
#define SOME_PROT_IDK


void print_array(int * arr, int len);
void print_sudoku_field(int width, int height, int ** sudoku_field);

int random_range(int l, int u);
int * range_array(int l, int u);
int * n_times_array(int num, int n);
int len_without(int * arr, int len, int x);
int random_choice_index_without(int * arr, int len, int x);
int ** create_sudoku_field(int width, int height);
int *** create_check_array(int width, int height);
void remove_possible_squares(int * arr, int len);
void remove_same_section(int square_index, int width, int height, int ** arr);
void remove_other_sections(int section, int value, int square, int width, int height, int *** arr);
int sum_array(int * arr, int len);
int random_value(int ** arr, int len);
void create_sudoku_puzzle(int width, int height);



#endif