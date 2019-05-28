/*
** EPITECH PROJECT, 2017
** GetNextLine
** File description:
** Created by antoine_dh,
*/

#include <string.h>
#include "get_next_line.h"

static char *strncat_dup(char *dest, char const *src, size_t size)
{
    size_t len = (dest == NULL) ? size + 1 : strlen(dest) + size + 1;
    char *str = malloc(sizeof(char) * len);

    if (str == NULL)
        return (NULL);
    for (size_t i = 0 ; i < len ; i++)
        str[i] = '\0';
    if (dest != NULL) {
        for (size_t i = 0 ; i < strlen(dest) ; i++)
            str[i] = dest[i];
        free(dest);
    }
    for (size_t i = len - size - 1 ; i < len - 1 ; i++)
        str[i] = src[i - (len - size - 1)];
    return (str);
}

static char *get_line_from_buff(char buffer[], int fd, size_t *pos,
    ssize_t *readsize)
{
    char *line = NULL;
    size_t i = 0;

    while (*readsize > 0 && buffer[*pos + i] != '\n') {
        if (*pos + i > READ_SIZE || buffer[*pos + i] == '\0') {
            line = strncat_dup(line, &buffer[*pos], i);
            *readsize = read(fd, buffer, READ_SIZE);
            memset(&buffer[*readsize == -1 ? 0 : *readsize], '\0',
                (size_t)(READ_SIZE - *readsize));
            *pos = 0;
            i = 0;
        } else
            i++;
    }
    line = strncat_dup(line, &buffer[*pos], i);
    *pos = *pos + i + 1;
    return (line);
}

char *get_next_line(int fd)
{
    static size_t pos = 0;
    ssize_t readsize = 1;
    static char buffer[READ_SIZE + 1] = "";
    char *line = get_line_from_buff(buffer, fd, &pos, &readsize);

    memset(buffer, '\0', pos);
    if (readsize > 0 || strlen(line) > 0)
        return (line);
    if (line != NULL)
        free(line);
    return (NULL);
}
