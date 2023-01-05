#include <stdio.h>

int len_s(char* str) {
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

int compare_s(char* s1, char* s2) {
    for (int i = 0; i < len_s(s1); ++i) {
        if (s1[i] != s2[i])
            return 0;
    }
    return 1;
}

void slice_s(char* string, char* slice, int start, int end) {
    if (start > end || start < 0 || end >= len_s(string))
        return;
    int size = sizeof(char);
    int j = 0;
    for (int i = start; i < end + 1; ++i) {
        slice[j] = string[i];
        j++;
    }
}

int substring_s(char* str, char* sub) {
    if (len_s(str) < len_s(sub))
        return 0;
    else if (len_s(str) == len_s(sub))
        return compare_s(str, sub);
    for (int i = 0; i < len_s(str) - len_s(sub) + 1; ++i) {
        char slice[20];
        slice_s(str, slice, i, i + len_s(sub) - 1);
        if (compare_s(slice, sub) == 1) {
            return 1;
        }
    }
    return 0;
}

int main() {
    char string[20];
    printf("string: ");
    scanf("%s", string);
    char sub_string[20];
    printf("substring: ");
    scanf("%s", sub_string);

    printf("%s\n", substring_s(string, sub_string) == 1 ? "true" : "false");
}