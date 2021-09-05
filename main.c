#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include "my_stdlib.h"

const int true = 1;

int checkString(char* str) {
    char *p = str;
    while (isspace( (unsigned char ) *p)) ++p;
    return (*p == '\0' || *p == '\n') ? 0 : 1;
}

int checking(const char* cur) {
    char* checkString = "[]1234567890IVXL.,;…'";
    while (*checkString) {
        if (*cur == *checkString) {
            return 0;
        }
        checkString++;
    }
    return 1;
}

int strcmp_modified(const char* str1, const char* str2) {
    while (*str1 == *str2 && checking(str1) && checking(str2)) {
        if (!checking(str1) || (!checking(str2))) {
            if (!checking(str1)) {
                str1++;
            }
            if (!checking(str2)) {
                str2++;
            }
        } else {
            str1++;
            str2++;
        }

    }
    if (*str1 == *str2) {
        return 0;
    }
    return *str1 > *str2 ? 1 : -1;
}

int readLine(FILE *in, char *buffer, size_t max) {
    return fgets(buffer, (int) max, in) == buffer;
}

void swap(char** a, size_t i, size_t j) {
    char* tmp = a[j];
    a[j] = a[i];
    a[i] =  tmp;
}

size_t partition(char** a, size_t l, size_t r) {
    char* pivot = a[(l + r) / 2];
    size_t i = l, j = r;
    while (true) {
        while (strcmp_modified(a[i], pivot) == -1) i++;
        while (strcmp_modified(a[j], pivot) == 1) j--;
        if (i >= j) {
            return j;
        }
        swap(a, i++, j--);
    }
}

void quicksort(char** a, size_t l, size_t r) {
    if (l < r) {
        size_t p = partition(a, l, r);
        quicksort(a, l, p);
        quicksort(a, p + 1, r);
    }
}

void StartSorting() {
    FILE* onegin = fopen("onegin.txt", "r");
    if (onegin == NULL) {
        printf("something unexpected happened \n");
        return;
    }

    char** strings = (char**) malloc(sizeof (char*));
    size_t elementNumber = 0;
    while (!feof(onegin)) {
        char* str = (char*) malloc(sizeof (char) * 256);
        if (!readLine(onegin, str, 256)) {
            break;
        }
        if (checkString(str)) {
            strings[elementNumber] = str;
            elementNumber++;
            strings = (char**) realloc(strings, sizeof (char*) * (elementNumber + 1));
        }
    }
    quicksort(strings, 0, elementNumber - 1);
    for (size_t i = 0; i < 20; ++i) {
        puts(strings[i]);
    }
}

int main() {
    StartSorting();
    return 0;
}
