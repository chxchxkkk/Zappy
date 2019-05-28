/*
** EPITECH PROJECT, 2019
** zappy
** File description:
** Created by antoine_dh,
*/


#include <malloc.h>
#include <string.h>
#include <stdbool.h>
#include <stdarg.h>

size_t strarr_len(char *const *array)
{
    for (size_t i = 0 ;; ++i)
        if (array[i] == NULL)
            return (i);
}

char *str_rstrip(char *str, const char *to_strip)
{
    size_t len;

    if (str == NULL)
        return (NULL);
    len = strlen(str);
    for (size_t i = len ; i > 0 ; --i) {
        if (strchr(to_strip, str[i - 1]) != NULL)
            str[i - 1] = '\0';
        else
            break;
    }
    return (str);
}

char *str_lstrip(char *str, const char *to_strip)
{
    char *new = str;
    size_t len;

    if (str == NULL)
        return (NULL);
    len = strlen(str);
    for (size_t i = 0 ; i < len ; ++i) {
        if (strchr(to_strip, str[i]) != NULL)
            new++;
        else
            break;
    }
    new = strdup(new);
    free(str);
    return (new);
}

char *str_strip(char *str, const char *to_strip)
{
    return (str_lstrip(str_rstrip(str, to_strip), to_strip));
}

char *va_strcat(bool _free, size_t n, ...)
{
    char *arr[n];
    char *str;
    size_t len = 0;
    va_list ap;

    va_start(ap, n);
    for (size_t i = 0 ; i < n ; ++i) {
        arr[i] = va_arg(ap, char *);
        len += strlen(arr[i]);
    }
    va_end(ap);
    if ((str = calloc(len + 1, sizeof(char))) == NULL)
        return (NULL);
    for (size_t i = 0 ; i < n ; ++i) {
        strcat(str, arr[i]);
        if (_free)
            free(arr[i]);
    }
    return (str);
}
