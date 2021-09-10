#include <stdio.h>
#include <malloc.h>
#include <ctype.h>

const int true = 1;


int checking (const char* cur) {
    char* checkString = "[]<*?>1234567890IVXL«»—-().,;…' ";
    while (*checkString) {
        if (*cur == *checkString) {
            return 0;
        }
        checkString++;
    }
    return 1;
}

int checkString (char* str) {
    char* p = str;
    while (isspace( (unsigned char ) *p) || !checking(p)) ++p;
    return (*p == '\0' || *p == '\n') ? 0 : 1;
}

int strcmp_modified (const char* str1, const char* str2) {
    while (true) {
        if (!*str1) {
            if (*str1 == '\0' || *str1 == '\n') {
                break;
            }
            str1++;
            continue;
        }
        if (!*str1) {
            if (*str1 == '\0' || *str1 == '\n') {
                break;
            }
            str1++;
            continue;
        }
        if (*str1 != *str2) {
            break;
        }
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

int readLine (FILE *in, char *buffer, size_t max) {
    return fgets(buffer, (int) max, in) == buffer;
}

void swap (char** a, size_t i, size_t j) {
    char* tmp = a[j];
    a[j] = a[i];
    a[i] =  tmp;
}

size_t partition (char** a, size_t l, size_t r) {
    char* pivot = a[(l + r) / 2];
    size_t i = l, j = r;
    while (true) {
        while (strcmp_modified(a[i], pivot) < 0) i++;
        while (strcmp_modified(a[j], pivot) > 0) j--;
        if (i >= j) {
            return j;
        }
        swap(a, i++, j--);
    }
}

void quicksort (char** a, size_t l, size_t r) {
    if (l < r) {
        size_t p = partition(a, l, r);
        quicksort(a, l, p);
        quicksort(a, p + 1, r);
    }
}

void StartSorting () {
    FILE* onegin = fopen("onegin.txt", "r");
    if (onegin == NULL) {
        printf("Something unexpected happened, can't open 'onegin.txt'. \n");
        return;
    }
    printf("Successfully opened 'onegin.txt' file. \n");

    char** strings = (char**) malloc(sizeof (char*));
    size_t elementNumber = 0;

    while (!feof(onegin)) {
        char* str = (char*) malloc(sizeof (char) * 600);
        if (!readLine(onegin, str, 600)) {
            break;
        }
        if (checkString(str)) {
            strings[elementNumber] = str;
            elementNumber++;
            strings = (char**) realloc(strings, sizeof (char*) * (elementNumber + 1));
        }
    }

    fclose(onegin);
    printf("Successfully finished reading strings from 'onegin.txt' \n"
           "Total strings = %zu \n", elementNumber);

    printf("Launching quicksort... Done. \n");
    quicksort(strings, 0, elementNumber - 1);
    printf("Finishing sorting the array... Done. \n");

    FILE* onegin_out = fopen("onegin_sorted.txt", "w");
    if (onegin_out == NULL) {
        printf("Something unexpected happened, can't open 'onegin_sorted.txt'. \n");
        return;
    }
    fflush(onegin_out);
    printf("Starting writing to 'onegin_sorted.txt'. \n");

    for (size_t current_string = 0; current_string < elementNumber; ++current_string) {
        fputs(strings[current_string], onegin_out);
    }

    printf("Finished writing to 'onegin_sorted.txt'. \n");
    fclose(onegin_out);
}

int main() {
    StartSorting();
    return 0;
}

/*
char getChar(FILE* in, char* cur) {
    int check = fscanf(in, "%c", cur);
    if (!check || !checking(cur)) {
        return -1;
    }
    return *cur;
}

size_t arrLen(char** a) {
    size_t len = 0;
    while (a) {
        len++;
        a++;
    }
    return len;
}


void* myFGets(char* buffer, size_t max, FILE* in) {
    char cur = -2;
    size_t curSize = 0;
    while (curSize < max) {
        if (cur != getChar(in, &cur)) {
            continue;
        }
        buffer[curSize] = cur;
        curSize += 1;
    }
    buffer[curSize] = '\0';
    return buffer;
}
*/
