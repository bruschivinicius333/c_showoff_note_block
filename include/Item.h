#pragma once

#include <stdbool.h>
#include <stdio.h>

#define ITEM_TITLE_LENGTH 128
#define ITEM_TEXT_LENGTH 2048

#define FILE_NOTE   "notes.csv"
#define FILE_TASK   "tasks.csv"
#define FILE_EVENT  "events.csv"

typedef struct Item Item;

typedef enum {
    NOTE = 1,
    TASK = 2,
    EVENT = 3
} item_type;

Item *item_create(const char *title, char *text, item_type type);

void item_print(void *this);

void item_destroy(Item **this);

bool item_match(void *cmp1, void *cmp2);

void *item_csv_readField(char *token);

void item_csv_fprintf(FILE *, void *this);

void item_note_print(void *print);
void item_task_print(void *print);
void item_event_print(void *print);

void item_csv_clear();

bool item_note_match(void *, void *);
bool item_task_match(void *, void *);
bool item_event_match(void *, void *);

bool item_note_is(void *cmp);
bool item_task_is(void *cmp);
bool item_event_is(void *cmp);