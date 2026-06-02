#include "../include/Item.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

struct Item {
    char title[ITEM_TITLE_LENGTH];
    char text[ITEM_TEXT_LENGTH];
    item_type type;
};

Item *item_create(const char *title, char *text, item_type type) {
    Item *create = malloc(sizeof(Item));
    if (!create) return NULL;
    snprintf(create->title, sizeof(create->title), "%s", title ? title : "");
    snprintf(create->text,  sizeof(create->text),  "%s", text  ? text  : "");
    create->type = type;
    return create;
}

void item_print(void *this) {
    if (!this) return;
    printf("\n");
    printf("Title: %s\n", ((Item *)this)->title);
    printf("Text: %s\n",  ((Item *)this)->text);
    printf("Item type: ");
    switch (((Item *)this)->type) {
        case NOTE:  printf("Note\n");  break;
        case TASK:  printf("Task\n");  break;
        case EVENT: printf("Event\n"); break;
        default: printf("None?: %d\n", ((Item *)this)->type);
    }
}

void item_destroy(Item **this) {
    if (!this || !*this) return;
    free(*this);
    *this = NULL;
}

bool item_match(void *cmp1, void *cmp2) {
    if (!cmp1 || !cmp2) return false;
    return !strcmp(((Item *)cmp1)->title, ((Item *)cmp2)->title);
}

void *item_csv_readField(char *token) {
    static Item toInsert = {0};
    static bool shouldReset = false;

    if (shouldReset) {
        *toInsert.title = '\0';
        *toInsert.text  = '\0';
        toInsert.type   = 0;
        shouldReset = false;
    }

    if (!token) return NULL;

    if (!*toInsert.title) {
        snprintf(toInsert.title, sizeof(toInsert.title), "%s", token);
    } else if(!*toInsert.text) {
        snprintf(toInsert.text, sizeof(toInsert.text), "%s", token);   
    } else {
        toInsert.type = atol(token);
        shouldReset = true;
        return item_create(toInsert.title, toInsert.text, toInsert.type);
    }

    return NULL;
}

void item_csv_clear() {
    fclose(fopen(FILE_NOTE, "w"));
    fclose(fopen(FILE_TASK, "w"));
    fclose(fopen(FILE_EVENT, "w"));
}

void item_csv_fprintf(FILE *fp, void *this) {
    (void)fp;
    Item *item = (Item *)this;

    const char *file = NULL;
    if      (item->type == NOTE)  file = FILE_NOTE;
    else if (item->type == TASK)  file = FILE_TASK;
    else if (item->type == EVENT) file = FILE_EVENT;

    if (!file) return;

    FILE *dest = fopen(file, "a");
    if (!dest) return;

    fprintf(dest, "%s,%s,%d\n", item->title, item->text, item->type);
    fclose(dest);
}

void item_note_print(void *print) {
    if(((Item *)print)->type == NOTE) item_print(print);
}

void item_task_print(void *print) {
    if(((Item *)print)->type == TASK) item_print(print);
}

void item_event_print(void *print) {
    if(((Item *)print)->type == EVENT) item_print(print);
}

bool item_note_match(void *cmp1, void *cmp2) {
    return (item_match(cmp1, cmp2) && ((Item *)cmp1)->type == NOTE);
}
bool item_task_match(void *cmp1, void *cmp2) {
    return (item_match(cmp1, cmp2) && ((Item *)cmp1)->type == TASK);
}
bool item_event_match(void *cmp1, void *cmp2) {
    return (item_match(cmp1, cmp2) && ((Item *)cmp1)->type == EVENT);
}

bool item_note_is(void *cmp) {
    return ((Item *)cmp)->type == NOTE;
}
bool item_task_is(void *cmp) {
    return ((Item *)cmp)->type == TASK;
}
bool item_event_is(void *cmp) {
    return ((Item *)cmp)->type == EVENT;
}
