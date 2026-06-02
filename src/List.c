#include "../include/List.h"

#include <stdio.h>
#include <stdlib.h>

struct List {
    void *data;
    struct List *next;
};

List *list_create() {
    return NULL;
}

List *list_last(List *list) {
    for(List *cur = list; cur; cur = cur->next) {
        if(!cur->next) {
            return cur;
        }
    }
    return NULL;
}

int list_push(List **list, void *data) {
    if (!list) return 1;

    List *node = malloc(sizeof(List));
    if (!node) return 1;

    node->data = data;
    node->next = NULL;

    if (!*list) {
        *list = node;
        return 0;
    }

    List *cur = *list;
    while (cur->next) {
        cur = cur->next;
    }
    cur->next = node;

    return 0;
}

void list_print(List *this, void (*run)(void *data)) {
    if(!this) {
        printf("Empty list\n");
        return;
    }
    for(List *cur = this; cur; cur = cur->next) {
        run(cur->data);
    }
}

int list_shift(List **list) {

    if(!list || !*list) return 1;

    List *toFree = (*list);

    (*list) = (*list)->next;

    free(toFree->data);

    free(toFree);
    toFree = NULL;

    return 0;
}

int list_destroy(List **list) {
    if(!list || !*list) return 0;
    while(!list_shift(list));
    return 0;
}

int list_append(List **this, List **other) {
    if (!this || !other || !*other)
        return 1;

    if (!*this) {
        *this = *other;
        *other = NULL;
        return 0;
    }

    List *last = NULL;
    for (List *cur = *this; cur; cur = cur->next) {
        if (cur == *other)
            return 1;
        last = cur;
    }

    last->next = *other;
    *other = NULL;

    return 0;
}

void *list_find(List *this, void *cmp, bool (*run)(void *, void *)) {
    for(List *cur = this; cur; cur = cur->next) {
        if(run(cur->data, cmp))
            return cur->data;
    }
    return NULL;
}

void list_csv_read(const char *fileName, List **list, void *(*listtype_csv_readField)(char *token)) {
    FILE *mainFile = fopen(fileName, "r");

    if(!mainFile) {
        fprintf(stderr, "Error in list_csv_read: file does not exist\n");
        return;
    }

    char *token = NULL;

    void *toInsert = NULL;
    while((token = csv_next(mainFile))) {

        if((toInsert = listtype_csv_readField(token))) {
            list_push(list, toInsert);
        }

    }

    fclose(mainFile);
}

void list_csv_write(
    const char *fileName,
    List **list,
    void (*listtype_csv_fprintf)(FILE *, void *)
) {
    
    if (!list || !listtype_csv_fprintf) return;

    FILE *mainFile = fopen(fileName, "w");

    while (!list_isEmpty(*list)) {

        List *node = *list;

        listtype_csv_fprintf(mainFile, node->data);

        list_shift(list);
    }

    if(mainFile) fclose(mainFile);
}

int list_pop(List **this) {
    if(!this || !*this) return 1;
    
    List *cur = *this;

    // Single element
    if (!cur->next) {
        free(cur->data);
        free(cur);
        *this = NULL;
        return 0;
    }

    // Find penultimate
    while (cur->next->next) {
        cur = cur->next;
    }

    free(cur->next->data);
    free(cur->next);
    cur->next = NULL;

    return 0;
}

bool list_isEmpty(const List *this) {
    return (!this);
}

int list_delete(
    List **list,
    void *find,
    bool (*cmp)(void *data, void *find)
) {
    if (!list || !*list || !find || !cmp) return 1;

    List *cur = *list;
    List *prev = NULL;

    while (cur) {

        if (cmp(cur->data, find)) {

            if (prev)
                prev->next = cur->next;
            else
                *list = cur->next;

            free(cur->data);
            free(cur);

            return 0;
        }

        prev = cur;
        cur = cur->next;
    }

    return 1;
}

size_t list_length(List *list) {

    size_t length = 0;

    for (List *cur = list; cur; cur = cur->next)
        length++;

    return length;
}

size_t list_count(List *list, bool (*cmp)(void *)) {

    if (!cmp)
        return 0;

    size_t count = 0;

    for (List *cur = list; cur; cur = cur->next) {
        if (cmp(cur->data))
            count++;
    }

    return count;
}