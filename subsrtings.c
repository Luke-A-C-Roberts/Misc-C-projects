#include <stdio.h>

int len_str(char* str) {
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len;
}

int compare_str(char* s1, char* s2) {
    for (int i = 0; i < len_s(s1); ++i) {
        if (s1[i] != s2[i])
            return 0;
    }
    return 1;
}

void slice_str(char* string, char* slice, int start, int end) {
    if (start > end || start < 0 || end >= len_s(string))
        return;
    int size = sizeof(char);
    int j = 0;
    for (int i = start; i < end + 1; ++i) {
        slice[j] = string[i];
        j++;
    }
}

int substring_str(char* str, char* sub) {
    if (len_str(str) < len_str(sub))
        return 0;
    else if (len_str(str) == len_str(sub))
        return compare_str(str, sub);
    for (int i = 0; i < len_str(str) - len_str(sub) + 1; ++i) {
        char slice[20];
        slice_str(str, slice, i, i + len_str(sub) - 1);
        if (compare_str(slice, sub) == 1) {
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

    printf("%s\n", substring_str(string, sub_string) == 1 ? "true" : "false");
}
