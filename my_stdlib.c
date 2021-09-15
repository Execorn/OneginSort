#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "my_stdlib.h"

//
// Created by Legion on 29.08.2021.
//


int puts (const char* str) {
    assert(str != NULL);

    while (*str != '\0') {
        int check = printf("%c", *str);
        if (check < 0) {
            return check;
        }
        str++;
    }

    return printf("\n");
}

const char* strchr (const char *str, const int ch) {
    assert(str != NULL);
    assert(0 < ch && ch < 128);

    while (*str != '\0') {
        if (*str == (char) ch) {
            return str;
        }
        str++;
    }

    return NULL;
}


size_t strlen (const char *str) {
    assert(str != NULL);
    size_t current_len = 0;

    while (str[current_len] != '\0') {
        current_len++;
    }

    return current_len;
}

char* strcpy (char *destination, const char *source) {
    assert(destination != NULL);
    assert(source != NULL);

    for (size_t i = 0; source[i]; ++i) {
        destination[i] = source[i];
    }
    return destination;
}

char* strncpy (char *destination, const char *source, size_t n) {
    assert(destination != NULL);
    assert(source != NULL);
    assert(0 <= n && n <= strlen(source));

    for (size_t i = 0; source[i] && i < n; ++i) {
        destination[i] = source[i];
    }
    return destination;
}

char* strcat (char *destination, const char *append) {
    assert(destination != NULL);
    assert(append != NULL);

    for (size_t i = strlen(destination); *append; i++) {
        destination[i] = *append;
        *append++;
    }

    return destination;
}

char* strncat (char *destination, const char *append, size_t n) {
    assert(destination != NULL);
    assert(append != NULL);
    assert(n <= strlen(append));

    size_t current_append_index = 0;
    for (size_t i = strlen(destination); *append && current_append_index < n; i++) {
        destination[i] = *append;
        *append++;
        current_append_index++;
    }

    return destination;
}


char* strdup (const char *str) {
    char* result = malloc(sizeof(char) * strlen(str));
    if (!result) return NULL;
    strcpy(result, str);
    return result;
}

int strcmp(const char *str1, const char *str2) {
    while (*(str1++) == *(str2++) && *str1 && *str2);
    if (*str1 == *str2) {
        return 0;
    }
    return *str1 > *str2 ? 1 : -1;
}
