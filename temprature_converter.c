#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void partition(char* input, double* parameters) {
    char* partition = strtok(input, " ");
    int i = 0;
    while (partition) {
        parameters[i] = atof(partition);
        partition = strtok(NULL, " ");
        i = i + 1;
    }
}

int main() {
    char raw_input[200];
    double parameters[4] = {0, 0, 0, 0};
    fgets(raw_input, sizeof(raw_input), stdin);
    partition(raw_input, parameters);
    printf("Celsius\t\tFarenheit\n--------\t--------\n");
    for (double i = parameters[0]; i < parameters[1]; i += parameters[2]) {
        printf("%f'C\t%f'F\n", i, i * 9 / 5 + 32);
    }
    return 0;
}