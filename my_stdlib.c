#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include "my_stdlib.h"

//
// Created by Legion on 29.08.2021.
//

/*!
 * \brief Функция, выводящая поданную на вход строку в поток stdout.
 *
 * @param [in] str указатель на массив char-ов (строку).
 *
 * Возвращает отрицательное значение в случае невозможности записи строки (EOF).
 * Иначе, возвращает 1.
 */

int puts (const char* str) {
    assert(str != NULL);

    while (*str != '\0') {
        int check = printf("%c", *str);
        if (check < 0) {
            return check;
        }
        str++;
    }

    // return printf("\n");
}


/*!
 * \brief Функция, возвращающая указатель на первый встретившийся заданный элемент строки.
 *
 * @param [in] str указатель на строку.
 * @param [in] ch значение типа char, поиск которого выполняется в строке.
 * @param [out] str указатель на первый элемент элемент строки, равный ch.
 *
 * Возвращает NULL в случае отсутствия подходящего элемента в входной строке.
 */

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


/*!
 * \brief Функция, возвращающая длину поданной на вход строки.
 *
 * @param [in] str указатель на массив char-ов (строку).
 * @param [out] current_len (size_t) количество символов в строке без нулевого символа.
 */

size_t strlen (const char *str) {
    assert(str != NULL);
    size_t current_len = 0;

    while (str[current_len] != '\0') {
        current_len++;
    }

    return current_len;
}


/*!
 * \brief Функция, копирующая содержимое одной строки в другую.
 *
 * @param [in] destination строка, в которую выполняется копирование.
 * @param [in] source строка, копируемая в destination.
 * @param [out] destination строка, в которую было скопировано содержимое source.
 */

char* strcpy (char *destination, const char *source) {
    assert(destination != NULL);
    assert(source != NULL);

    for (size_t i = 0; source[i]; ++i) {
        destination[i] = source[i];
    }
    return destination;
}


/*!
 * \brief Функция, копирующая содержимое одной строки в другую по заданному количеству символов.
 *
 * @param [in] destination строка, в которую выполняется копирование.
 * @param [in] source строка, копируемая в destination.
 * @param [in] n количество символов, которые необходимо скопировать.
 * @param [out] destination строка, в которую было скопировано содержимое source.
 */

char* strncpy (char *destination, const char *source, size_t n) {
    assert(destination != NULL);
    assert(source != NULL);
    assert(0 <= n && n <= strlen(source));

    for (size_t i = 0; source[i] && i < n; ++i) {
        destination[i] = source[i];
    }
    return destination;
}


/*!
 * \brief Функция, выполняющая конкатенацию двух строк.
 *
 * @param [in] destination строка, к которой конкатенируется другая строка.
 * @param [in] source строка, добавляемая к destination.
 * @param [out] destination строка, получившаяся в результате конкатенации строк.
 */

char* strcat (char *destination, const char *append) {
    assert(destination != NULL);
    assert(append != NULL);

    for (size_t i = strlen(destination); *append; i++) {
        destination[i] = *append;
        *append++;
    }

    return destination;
}


/*!
 * \brief Функция, выполняющая конкатенацию двух строк по заданному количеству символов прибавляемой строки.
 *
 * @param [in] destination строка, к которой конкатенируется другая строка.
 * @param [in] source строка, добавляемая к destination.
 * @param [in] n количество символов строки source, необходимых добавить к destination.
 * @param [out] destination строка, получившаяся в результате конкатенации строк.
 */

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


/*!
 * \brief Функция, копирующая входную строку и самостоятельно выделяющая память.
 *
 * @param [in] str дуплицируемая строка.
 * @param [out] result динамически созданная строка, идентичная входной.
 */

char* strdup (const char *str) {
    char* result = malloc(sizeof(char) * strlen(str));
    if (!result) return NULL;
    strcpy(result, str);
    return result;
}


/*!
 * \brief Функция, сравнивающая две строки.
 *
 * @param [in] str1 первая строка для сравнения.
 * @param [in] str2 вторая строка для сравнения.
 *
 *
 * Строки сравниваются лексикографически. Если str1 > str2, функция возвращает 1.
 * В случае эквивалентности строк функция возвращает 0.
 * В случае, если str1 < str2, возвращаемое значение равно -1.
 */

int strcmp(const char *str1, const char *str2) {
    while (*(str1++) == *(str2++) && *str1 && *str2);
    if (*str1 == *str2) {
        return 0;
    }
    return *str1 > *str2 ? 1 : -1;
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
