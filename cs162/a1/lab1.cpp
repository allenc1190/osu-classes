#include <iostream>
#include <cstdlib>

using namespace std;

//Define struct here
    struct mult_div_values {
        int mult;
        float div;
    };
   

bool is_valid_dimensions(int argc, char **argv, int *rows, int *cols){
    if(argc < 3){
        cout << "Enter a.out [rows] [columns]" << endl;
        return 1;
    }
    *rows = atoi(argv[1]);
    *cols = atoi(argv[2]);
    if(*rows < 1 || *cols < 1){
        cout << "Enter only non-zero integer values for rows and columns" << endl;
        return 1;
    }

}

mult_div_values** create_table(int rows, int cols){
    int **table = new int*[rows];
    for(int i = 0; i < rows; i++){
        table[i] = new int[cols];
    }
}

void set_mult_values(mult_div_values **table, int rows, int cols){
    int mult;

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; i++) {;
            //table[i][j] = i * j;
        }
    }
}

void set_div_values(mult_div_values **table, int rows, int cols);

void delete_table(mult_div_values **table, int rows);

int main(int argc, char **argv) {
    int rows, cols;

    is_valid_dimensions(argc, argv, rows, cols);

    /*for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; i++){
            cout << array[i][j] << " ";
        }
        cout << endl;   
    }

    for(int i = 0; i < argc; i++){
        cout << i << ")" << argv[i] << endl;
    }*/

   //delete matrix
    
    return 0;
}
