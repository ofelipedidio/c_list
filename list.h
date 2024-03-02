#ifndef LIST
#define LIST

#include <stdlib.h>

// Implicit operations
// Get item  : list.items[i]
// Get length: list.length
// Clear list: list.length = 0

#define list_definition(T) \
    struct { \
        T *items; \
        size_t length; \
        size_t capacity; \
    }

#define list_init(list) \
    (list).capacity = 1; \
    (list).items = (typeof((list).items)) calloc((list).capacity, sizeof(typeof((list).items[0]))); \
    (list).length = 0;

#define list_init_with_capacity(list, cap) \
    (list).capacity = (cap); \
    (list).items = (typeof((list).items)) calloc((list).capacity, sizeof(typeof((list).items[0]))); \
    (list).length = 0;

#define list_push(list, item) \
    while ((list).length + 1 >= (list).capacity) { \
        size_t new_capacity = (list).capacity == 0 ? 1 : (list).capacity * 2; \
        typeof((list).items) new_array = (typeof((list).items)) reallocarray((list).items, new_capacity, sizeof(typeof((list).items[0]))); \
        (list).items = new_array; \
        (list).capacity = new_capacity; \
    } \
    (list).items[(list).length] = (item); \
    (list).length++;

#define list_insert(list, item, index) \
{ \
    size_t idx = (index); \
    while ((list).length + 1 >= (list).capacity) { \
        size_t new_capacity = (list).capacity == 0 ? 1 : (list).capacity * 2; \
        typeof((list).items) new_array = (typeof((list).items)) reallocarray((list).items, new_capacity, sizeof(typeof((list).items[0]))); \
        (list).items = new_array; \
        (list).capacity = new_capacity; \
    } \
    if (idx >= (list).length) { \
        (list).items[(list).length] = (item); \
    } else { \
        for (size_t i = (list).length-1; i >= idx; i--) { \
            (list).items[i+1] = (list).items[i]; \
        } \
        (list).items[idx] = (item); \
    } \
    (list).length++; \
}

#define list_remove(list, index) \
{ \
    size_t idx = (index); \
    for (size_t i = idx; i < (list).length-1; i++) { \
        (list).items[i] = (list).items[i+1]; \
    } \
    (list).length--; \
}

#define list_get(list, index) \
    (((index) < (list).length) ? &(list).items[(index)] : NULL)

#define list_free(list, destructor) \
{ \
    size_t list_free_length = (list).length; \
    for (size_t i = 0; i < list_free_length; i++) { \
        destructor \
    } \
    free((list).items); \
}

#define list_index_of(list, cmp, index_ptr) \
{ \
    index = -1; \
    for (size_t i = 0; i < (list).length; i++) { \
        if (cmp) { \
            (index) = i; \
        } \
    } \
}

#endif

