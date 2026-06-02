#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "reader.h"
#include "List.h"
#include "Item.h"

typedef enum {
    CREATE = 1,
    READ,
    DELETE,
    STATISTICS,
    EXIT
} menuOptions;

void main_insertItem(List **, item_type);

void main_readItem(List **, item_type);

void main_deleteItem(List **list, item_type);

void main_statistics(List **list);

void main_exit(List **list);

item_type main_whichItemType();

void main_retrieveFromCsv(List **list);
