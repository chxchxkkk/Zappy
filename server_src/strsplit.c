/*
** EPITECH PROJECT, 2017
** libmy
** File description:
** Created by antoine_dh,
*/

#include <string.h>
#include <malloc.h>

static size_t get_word_len(char const *str, char *delim)
{
    for (size_t i = 0 ;; i++)
        if (str[i] == '\0' || strchr(delim, str[i]) != NULL)
            return (i);
}

static size_t count_words(char const *str, char *delim)
{
    size_t words = 0;
    int i = 0;

    while (str[i]) {
        while (strchr(delim, str[i]) != NULL)
            i++;
        if (str[i])
            words++;
        while (strchr(delim, str[i]) == NULL && str[i])
            i++;
    }
    return (words);
}

char **str_split(char const *str, char *delim)
{
    size_t size = count_words(str, delim);
    int i = 0;
    int j = 0;
    char **arr = malloc(sizeof(char *) * (size + 1));

    if (arr == NULL)
        return (NULL);
    while (str[i]) {
        while (strchr(delim, str[i]) != NULL)
            i++;
        if (str[i]) {
            arr[j] = strndup(&str[i],
                get_word_len(&str[i], delim));
            j++;
        }
        while (strchr(delim, str[i]) == NULL && str[i])
            i++;
    }
    arr[size] = NULL;
    return (arr);
}
