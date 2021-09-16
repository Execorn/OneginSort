#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <alloca.h>
#include <stdint.h>
#include <stdlib.h>


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
            uint64_t tmp = *(uint64_t*) a;
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
        size_t bytes = (size >= 8 ? 8 : (size >= 4 ? 4 : (size >= 2 ? 2 : 1) ) );
        a += bytes;
        b += bytes;
        size -= bytes;
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
    const char* str1 = ((struct string*) a)->line;
    const char* str2 = ((struct string*) b)->line;
    int checker = strcmp(str1, str2);
    return !checker ? 1 : checker;
}

typedef struct {
    char* high;
    char* low;
} stackNode;


void quicksort (void* array, size_t count, size_t size, int (*comp) (const void *, const void *)) {
    char* mainPointer = (char*) array;

    if (count == 0) {
        return;
    }
    const size_t limit_thresh = size * 4;

    if (count > limit_thresh) {
        char* low = mainPointer;
        char* high = &low[size * (count - 1)];

        stackNode stack[(CHAR_BIT * sizeof (size_t))];
        stackNode* mainStack = stack;

        mainStack->low = NULL;
        mainStack->high = NULL;
        ++mainStack;

        while (stack < mainStack) {
            char* leftPointer;
            char* rightPointer;

            char* mid = low + size * ((high - low) / size >> 1);

            if ((*comp) ((void*) mid, (void *) low) < 0) {
                memorySwap(mid, low, size);
            }
            if ((*comp) ((void*) high, (void*) mid) < 0) {
                memorySwap(mid, high, size);
                if ((*comp) ((void*) mid, (void*) low) < 0) {
                    memorySwap(mid, low, size);
                }
            }

            leftPointer = low + size;
            rightPointer = high - size;

            do {
                while ((*comp) ((void*) leftPointer, (void*) mid) < 0) {
                    leftPointer += size;
                }
                while ((*comp) ((void*) mid, (void*) rightPointer) < 0) {
                    rightPointer -= size;
                }

                if (leftPointer < rightPointer) {
                    memorySwap(leftPointer, rightPointer, size);
                    if (mid == leftPointer) {
                        mid = rightPointer;
                    }
                    else if (mid == rightPointer) {
                        mid = leftPointer;
                    }
                    leftPointer += size;
                    rightPointer -= size;
                }
                else if (leftPointer >= rightPointer) {
                    leftPointer += size;
                    rightPointer -= size;
                    break;
                }
            } while (leftPointer <= rightPointer);


            if ((size_t) (rightPointer - low) <= limit_thresh) {
                if ((size_t) (high - leftPointer) <= limit_thresh) {
                    (void) (--mainStack, (low = mainStack->low), (high = mainStack->high));
                } else {
                    low = leftPointer;
                }
            } else if ((size_t) (high - leftPointer) <= limit_thresh) {
                high = rightPointer;
            } else if ((rightPointer - low) > (high - leftPointer)) {
                mainStack->low = low;
                mainStack->high = rightPointer;
                ++mainStack;
                low = leftPointer;
            } else {
                mainStack->low = leftPointer;
                mainStack->high = high;
                ++mainStack;
                high = rightPointer;
            }
        }
    }
    {
        char* const endPointer = &mainPointer[size * (count - 1)];
        char* tmpPointer = mainPointer;
        char* thresh = endPointer < mainPointer + limit_thresh ? endPointer : mainPointer + limit_thresh;
        char* runPointer;

        for (runPointer = tmpPointer + size; runPointer <= thresh; runPointer += size) {
            if ((*comp) ((void*) runPointer, (void*) tmpPointer) < 0) {
                tmpPointer = runPointer;
            }
            if (tmpPointer != mainPointer) {
                memorySwap(tmpPointer, mainPointer, size);
            }

            runPointer = mainPointer + size;
            while ((runPointer += size) <= endPointer) {
                tmpPointer = runPointer - size;
                while ((*comp) ((void*) runPointer, (void*) tmpPointer) < 0) {
                    tmpPointer -= size;
                }


                tmpPointer += size;
                if (tmpPointer != runPointer) {
                    char* rvt;

                    rvt = runPointer + size;
                    while (--rvt >= runPointer) {
                        char current = *rvt;
                        char *high, *low;

                        for (high = low = rvt; (low -= size) >= tmpPointer; high = low) {
                            *high = *low;
                        }
                        *high = current;
                    }
                }
            }
        }
    }
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
        strings[*totalStrings].line = line;
        strings[*totalStrings].length = strlen(line);
        (*totalStrings)++;
        strings = (struct string*) realloc(strings, sizeof (struct string) * (*totalStrings + 1));
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
    quicksort(strings, elementNumber - 1, sizeof(strings[0]), structComparator);
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
