#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <stdint.h>
#include "my_stdlib.h"

int my_isalnum (const unsigned char* cur) {
    return (*cur >= '0' && *cur <= '9') || (*cur >= 65 && *cur <= 90) || (*cur >= 97 && *cur <= 122);
}

struct string {
    char* line;
    size_t length;
};

void memorySwap(void* a, void* b, size_t size) {
    while (size) {
        if (size >= 8) {
            unsigned long long tmp = *(uint64_t*) a;
            *(uint64_t*) a = *(uint64_t*) b;
            *(uint64_t*) b = tmp;
        } else if (4 <= size && size < 8) {
            uint32_t tmp = *(uint32_t*) a;
            *(uint32_t*) a = *(uint32_t*) b;
            *(uint32_t*) b = tmp;
        } else if (2 <= size && size < 4) {
            uint16_t tmp = *(uint16_t*) a;
            *(uint16_t*) a = *(uint16_t*) b;
            *(uint16_t*) b = tmp;
        } else {
            uint8_t tmp = *(uint8_t*) a;
            *(uint8_t*) a = *(uint8_t*) b;
            *(uint8_t*) b = tmp;
        }
        a++; b++;
        size -= (size >= 8 ? 8 : (size >= 4 ? 4 : (size >= 2 ? 2 : 1) ) );
    }
}

int reverseStructComparator(const void* a, const void* b) {
    const struct string* firstStruct = (const struct string*) a;
    const struct string* secondStruct = (const struct string*) b;
    const char* str1 = firstStruct->line + firstStruct->length - 1;
    const char* str2 = secondStruct->line + secondStruct->length - 1;
    while (*str1 == *str2 && *str1 && *str2) {
        if (!my_isalnum((unsigned char*) str1)) {
            str1--;
            continue;
        }
        if (!my_isalnum((unsigned char*) str2)) {
            str2--;
            continue;
        }
        str1--; str2--;
    }
    return *str1 - *str2;
}

int structComparator(const void* a, const void* b) {
    const char* str1 = ((const struct string*) a)->line;
    const char* str2 = ((const struct string*) b)->line;
    while (*(str1++) == *(str2++) && *str1 && *str2);
    return *str1 - *str2;
}

void quicksort (void* array, size_t count, size_t size, int (*comp) (const void *, const void *)) {
    struct string* charArray = (struct string*) array;
    size_t left = 0, right = count - 1;
    void* pivot = charArray + count / 2;
    do {
        while (comp(charArray + left, pivot) < 0) left++;
        while (comp(charArray + right, pivot) > 0) right--;
        if (left >= right) {
            if (right > 0) {
                quicksort(charArray, right + 1, size, comp);
            }
            if (left < size) {
                quicksort(charArray + left, count - left, size, comp);
            }
        } else {
            memorySwap(charArray + left++, charArray + right--, size);
        }
    } while (left < right);
}

int checkString (char* str) {
    char* p = str;
    while (isspace( (unsigned char ) *p)) p++;
    return (*p == '\0' || *p == '\n') ? 0 : 1;
}

int readLine (FILE *in, char *buffer, size_t max) {
    return fgets(buffer, (int) max, in) == buffer;
}

int printOutput(struct string* strings, const size_t* elementNumber) {
    FILE* onegin_out = fopen("onegin_sorted.txt", "w");
    if (onegin_out == NULL) {
        printf("Something unexpected happened, can't open 'onegin_sorted.txt'. \n");
        return EOF;
    }
    printf("Starting writing to 'onegin_sorted.txt'. \n");

    for (size_t current_string = 0; current_string < *elementNumber; ++current_string) {
        fputs(strings[current_string].line, onegin_out);
    }

    printf("Finished writing to 'onegin_sorted.txt'. \n");
    fclose(onegin_out);
    return 0;
}

struct string* readToArray(FILE* in, size_t* totalStrings) {
    struct string* strings = (struct string*) malloc(sizeof (struct string));

    while (!feof(in)) {
        char* line = (char*) malloc(sizeof (char) * 600);
        if (!readLine(in, line, 600)) {
            break;
        }
        if (checkString(line)) {
            strings[*totalStrings].line = line;
            strings[*totalStrings].length = strlen(line);
            (*totalStrings)++;
            strings = (struct string*) realloc(strings, sizeof (struct string) * (*totalStrings + 1));
        }
    }
    return strings;
}

struct string* readText(size_t* elementNumber) {
    FILE* onegin = fopen("onegin.txt", "r");
    if (onegin == NULL) {
        printf("Something unexpected happened, can't open 'onegin.txt'. \n");
        return NULL;
    }
    printf("Successfully opened 'onegin.txt' file. \n");

    struct string* strings = readToArray(onegin, elementNumber);
    fclose(onegin);
    return strings;
}

void StartSorting () {
    size_t elementNumber = 0;
    struct string* strings = readText(&elementNumber);
    if (strings == NULL) {
        return;
    }
    printf("Successfully finished reading strings from 'onegin.txt' \n"
           "Total strings = %zu \n", elementNumber);


    printf("Launching quicksort... Done. \n");
    quicksort(strings, elementNumber, sizeof(strings[0]), structComparator);
    printf("Finishing sorting the array... Done. \n");

    int check = printOutput(strings, &elementNumber);
    if (check) {
        printf("writing to file failed. \n");
    }
    free(strings);
}

int main() {
    StartSorting();
    return 0;
}
