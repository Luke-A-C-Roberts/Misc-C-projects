//row_size = 1, row_ext = {1}

void itr_row(int* row = {1}, int* size_ptr = &row_size) {
    int size = *size_ptr; = 1
    int* new_row = malloc((2) * sizeof(int));
    for(int k = 0; k < 2; ++k) {
        if (k == 0 || k == size) {
            new_row[k] = 1;
        }
        else {
            new_row[k] = row[k] + row[k-1];
        }
    }
    *size_ptr++;
}