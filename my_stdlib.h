//
// Created by Legion on 29.08.2021.
//

#ifndef FUNCIMPLEMENTATION_MY_STDLIB_H
#define FUNCIMPLEMENTATION_MY_STDLIB_H


int puts (const char* str);

const char* strchr (const char *str, int ch);

size_t strlen (const char *str);

char* strcpy (char *destination, const char *source);

char* strncpy (char *destination, const char *source, size_t n);

char* strcat (char *destination, const char *append);

char* strncat (char *destination, const char *append, size_t n);

char* strdup (const char *str);

int strcmp(const char *str1, const char *str2);
#endif //FUNCIMPLEMENTATION_MY_STDLIB_H
