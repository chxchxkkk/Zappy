/*
** EPITECH PROJECT, 2017
** liblist
** File description:
** Created by antoine_dh,
*/

#ifndef LIBLIST_LIST_H
#define LIBLIST_LIST_H

#include <stdlib.h>

typedef struct list {
    struct list *next;
    struct list *prev;
} list_t;

#define LIST_NEXT(node) ((typeof(node))node->next)
#define LIST_PREV(node) ((typeof(node))node->prev)

typedef void (*list_del_t)(void *);

typedef int (*list_cmp_t)(const void *, const void *);

typedef int (*list_apply_t)(void *);

list_t *list_create_node(size_t size) __attribute__ ((alloc_size(1)));
void list_delete_node(list_t **begin, list_t *node, list_del_t del);
void list_free(list_t **begin, list_del_t del);
void list_concat(list_t **begin1, list_t **begin2);
list_t *list_append(list_t **begin, list_t *node);
list_t *list_push(list_t **begin, list_t *node);
void *list_pop(list_t **begin);
void list_sort(list_t **begin, list_cmp_t cmp);
list_t *list_insert(list_t *prev, list_t *node);
list_t *list_getlast(list_t *begin);
list_t *list_find_node(list_t *list, const list_t *node, list_cmp_t cmp);
list_t *list_add_sorted(list_t **begin, list_t *node, list_cmp_t cmp);
void list_merge(list_t **begin1, list_t *begin2, list_cmp_t cmp);
size_t list_size(const list_t *begin);
int list_delete_matching_nodes(list_t **begin, const list_t *node,
    list_cmp_t cmp, list_del_t del);
int list_apply_on_matching_nodes(list_t *list, list_apply_t func,
    const list_t *node, list_cmp_t cmp);
void list_reverse(list_t **begin);
void list_swap_nodes(list_t **begin, list_t *a, list_t *b);
list_t *list_at(list_t *begin, size_t index);

#define LIST_FOREACH(item, list, lambda)                                    \
({                                                                          \
    for (typeof(list) item = list ; item != NULL ; item = LIST_NEXT(item))  \
        lambda                                                              \
})

#define LIST_FIND(list, predicate)  \
({                                  \
    typeof(list) _node = NULL;      \
    LIST_FOREACH(it, list, {        \
        if ((predicate)) {          \
            _node = it;             \
            break;                  \
        }                           \
    });                             \
    _node;                          \
})

#define LIST_CREATE(type)    ((type *)list_create_node(sizeof(type)))
#define LIST_DELETE(begin, node, del)   (list_delete_node((list_t **)begin, \
    (list_t *)node, (list_del_t)del))
#define LIST_PUSH(list, node)   ((typeof(*list))list_push((list_t **)list,   \
    (list_t *)node))
#define LIST_FREE(begin, del)   (list_free((list_t **)begin, (list_del_t)del))
#define LIST_AT(begin, idx)     ((typeof(list))list_at((list_t *)begin, idx))

#endif //LIBLIST_LIST_H
