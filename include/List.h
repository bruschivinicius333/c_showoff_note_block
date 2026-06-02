#pragma once

#include <stdio.h>
#include <stdbool.h>

#include "reader.h"

typedef struct List List;

// the caller is responsible for calling each type of List with the proper function OF THE GIVEN DATA TYPE

List *list_create();
List *list_last(List *this);
int list_push(List **, void *);
void list_print(List *this, void (*run)(void *data));
int list_shift(List **this);
int list_destroy(List **this);
int list_append(List **this, List **other);
void *list_find(List *this, void *cmp, bool (*run)(void *, void *));
void list_csv_read(const char *fileName, List **list, void *(*listtype_csv_readField)(char *token));
void list_csv_write(const char *fileName, List **list, void (*listtype_csv_fprintf)(FILE *, void *));
bool list_isEmpty(const List *);
int list_delete(
    List **list,
    void *find,
    bool (*cmp)(void *data, void *find)
);
int list_pop(List **this);
size_t list_length(List *);
size_t list_count(List *, bool(*cmp)(void *));