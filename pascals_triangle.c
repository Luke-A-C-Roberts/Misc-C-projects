#include <stdio.h>
#include <stdlib.h>

//creates a next generation row
void itr_row(int* row, int size) {
    int* new_row = malloc((size + 1) * sizeof(int));
    for(int k = 0; k < size + 1; ++k)
        new_row[k] = (k == 0 || k == size)? 1 : row[k] + row[k-1];
    row = realloc(row, (size + 1) * sizeof(int));
    for (int i = 0; i < size + 1; ++i)
        row[i] = new_row[i];
    free(new_row);
}

void print_row(int* row, int size) {
    for (int i = 0; i < size; ++i) {
        printf("%d%s", row[i], ((i == size - 1)? "\n" : " "));
    }
}

int main() {
    int row_size = 1;
    int* row = malloc(row_size * sizeof(int));
    row[0] = 1;

    for (int i = 0; i < 5; ++i) {
        print_row(row, row_size);
        itr_row(row, row_size);
        row_size++;
    }
    print_row(row, row_size);

    free(row);
    return 0;
}