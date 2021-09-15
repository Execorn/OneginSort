//
// Created by Legion on 29.08.2021.
//

#ifndef FUNCIMPLEMENTATION_MY_STDLIB_H
#define FUNCIMPLEMENTATION_MY_STDLIB_H


/*!
 * \brief Функция, выводящая поданную на вход строку в поток stdout.
 *
 * @param [in] str указатель на массив char-ов (строку).
 *
 * @returns 1 если вывод строки прошел успешно (не EOF).
 * @returns 0 если функция не смогла вывести строку (EOF).
 */

int puts (const char* str);

/*!
 * \brief Функция, возвращающая указатель на первый встретившийся заданный элемент строки.
 *
 * @param [in] str указатель на строку.
 * @param [in] ch значение типа char, поиск которого выполняется в строке.
 * @param [out] str указатель на первый элемент элемент строки, равный ch.
 *
 * @returns NULL если элемент в строке не встретился.
 * @returns str указатель на элемент, если он встретился.
 */

const char* strchr (const char *str, int ch);

/*!
 * \brief Функция, возвращающая длину поданной на вход строки.
 *
 * @param [in] str указатель на массив char-ов (строку).
 * @returns current_len (size_t количество символов в строке без нулевого символа.
 */

size_t strlen (const char *str);

/*!
 * \brief Функция, копирующая содержимое одной строки в другую.
 *
 * @param [in] destination строка, в которую выполняется копирование.
 * @param [in] source строка, копируемая в destination.
 * @param [out] destination строка, в которую было скопировано содержимое source.
 * @returns destination указатель на первый элемент скопированной строки.
 */

char* strcpy (char *destination, const char *source);

/*!
 * \brief Функция, копирующая содержимое одной строки в другую по заданному количеству символов.
 *
 * @param [in] destination строка, в которую выполняется копирование.
 * @param [in] source строка, копируемая в destination.
 * @param [in] n количество символов, которые необходимо скопировать.
 * @param [out] destination строка, в которую было скопировано содержимое source.
 * @returns destination указатель на первый элемент скопированной части строки.
 */

char* strncpy (char *destination, const char *source, size_t n);

/*!
 * \brief Функция, выполняющая конкатенацию двух строк.
 *
 * @param [in] destination строка, к которой конкатенируется другая строка.
 * @param [in] source строка, добавляемая к destination.
 * @param [out] destination строка, получившаяся в результате конкатенации строк.
 * @returns destination указатель на первый элемент конкатенированной строки.
 */

char* strcat (char *destination, const char *append);

/*!
 * \brief Функция, выполняющая конкатенацию двух строк по заданному количеству символов прибавляемой строки.
 *
 * @param [in] destination строка, к которой конкатенируется другая строка.
 * @param [in] source строка, добавляемая к destination.
 * @param [in] n количество символов строки source, необходимых добавить к destination.
 * @param [out] destination строка, получившаяся в результате конкатенации строк.
 * @returns destination указатель на первый элемент конкатенированной строки по количеству символов.
 */

char* strncat (char *destination, const char *append, size_t n);

/*!
 * \brief Функция, копирующая входную строку и самостоятельно выделяющая память.
 *
 * @param [in] str дуплицируемая строка.
 * @param [out] result динамически созданная строка, идентичная входной.
 * @returns result указатель на первый элемент созданной строки.
 */

char* strdup (const char *str);

/*!
 * \brief Функция, сравнивающая две строки.
 *
 * @param [in] str1 первая строка для сравнения.
 * @param [in] str2 вторая строка для сравнения.
 *
 *
 * @returns 1 если str1 > str2
 * @returns 0 если str1 == str2
 * @returns -1 если str1 < str2
 */

int strcmp(const char *str1, const char *str2);

#endif //FUNCIMPLEMENTATION_MY_STDLIB_H
