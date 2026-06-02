#include "../include/main_functions.h"
#include "../include/reader.h"
#include "../include/Item.h"
#include "../include/List.h"

#include <ctype.h>

void csv_update(List **list) {
    item_csv_clear();
    list_csv_write("", list, item_csv_fprintf);
    list_csv_read(FILE_NOTE, list, item_csv_readField);
    list_csv_read(FILE_TASK, list, item_csv_readField);
    list_csv_read(FILE_EVENT, list, item_csv_readField);
}

/*int strupr(char *str) {
    if (!str) return 1;
    for (unsigned long i = 0; i < strlen(str); ++i)
        str[i] = toupper((unsigned char)str[i]);
    return 0;
}*/

void main_insertItem(List **list, item_type which) {
    char title[ITEM_TITLE_LENGTH];
    char text[ITEM_TEXT_LENGTH];
    strncpy(title, readInput("Title: "), ITEM_TITLE_LENGTH - 1);
    title[ITEM_TITLE_LENGTH - 1] = '\0';
    strncpy(text, readInput("Text: "), ITEM_TEXT_LENGTH - 1);
    text[ITEM_TEXT_LENGTH - 1] = '\0';

    list_push(list, item_create(title, text, which));
    csv_update(list);
}

void main_readItem(List **list, item_type which) {
    char option = 0;
    do {
        option = toupper((unsigned char)*readInput("Find (F) or List All (L)?: "));
    } while (!(option == 'F' || option == 'L'));

    switch (option) {
        case 'F': {
            Item *find = item_create(readInput("Title to find: "), NULL, 0);
            Item *found = NULL;
            switch(which) {
                case NOTE:  found = list_find(*list, find, item_note_match); break;
                case TASK:  found = list_find(*list, find, item_task_match); break;
                case EVENT: found = list_find(*list, find, item_event_match); break;
            }
            if (found) {
                item_print(found);
            } else {
                printf("\nNot found. Maybe (..?) with another type\n");
            }
            item_destroy(&find);
            break;
        }
        case 'L': {
            switch(which) {
                case NOTE:  list_print(*list, item_note_print); break;
                case TASK:  list_print(*list, item_task_print); break;
                case EVENT: list_print(*list, item_event_print); break;
            }
            break;
        }
    }
}

void main_deleteItem(List **list, item_type which) {

    Item *find = item_create(readInput("Title to find: "), NULL, 0);
    int failure = 0;
    switch(which) {
        case NOTE:  failure = list_delete(list, find, item_note_match); break;
        case TASK:  failure = list_delete(list, find, item_task_match); break;
        case EVENT: failure = list_delete(list, find, item_event_match); break;
    }
    if (!failure) {
        printf("\nSuccess on deletion\n");
    } else {
        printf("\nNot found. Maybe (..?) with another type\n");
    }
    item_destroy(&find);
    csv_update(list);
}

void main_statistics(List **list) {
    size_t totalNotes = list_count(*list, item_note_is);
    size_t totalTasks = list_count(*list, item_task_is);
    size_t totalEvents = list_count(*list, item_event_is);

    printf("\ntotalNotes: %lu\n", totalNotes);
    printf("totalTasks: %lu\n", totalTasks);
    printf("totalEvents: %lu\n", totalEvents);

    printf("\n");

    if (totalNotes == 0 && totalTasks == 0 && totalEvents == 0)
    printf("Absolutely nothing. Peak void.\n");

else if (totalNotes > totalTasks && totalNotes > totalEvents)
    printf("Oooh, I see you're well NOTEd!\n");

else if (totalTasks > totalNotes && totalTasks > totalEvents)
    printf("Damn, that's a lot of TASKS.\n");

else if (totalEvents > totalNotes && totalEvents > totalTasks)
    printf("Your calendar is fighting for its life.\n");

else if (totalNotes == totalTasks && totalTasks == totalEvents)
    printf("Perfect balance. Statistically weird.\n");

else if (totalTasks == 0 && totalEvents == 0)
    printf("You only write notes. Professional overthinker.\n");

else if (totalNotes == 0 && totalEvents == 0)
    printf("Tasks only. Industrial behavior.\n");

else if (totalNotes == 0 && totalTasks == 0)
    printf("Events only. You live by the clock.\n");

else if (totalTasks > 20)
    printf("That's not productivity anymore. That's damage.\n");

else if (totalEvents > 15)
    printf("Your schedule looks terminal.\n");

else if (totalNotes > 50)
    printf("You archive thoughts like a surveillance state.\n");

else if (totalTasks > totalNotes + totalEvents)
    printf("You create work faster than you finish it.\n");

else if (totalEvents > totalNotes + totalTasks)
    printf("Every minute of your life is apparently booked.\n");

else if (totalNotes > totalTasks + totalEvents)
    printf("You document more than you act.\n");

else
    printf("Mild chaos. Functional enough.\n");
}

void main_exit(List **list) {
    item_csv_clear();
    list_csv_write("", list, item_csv_fprintf);
    list_destroy(list);

    exit(EXIT_SUCCESS);
}

void main_retrieveFromCsv(List **list) {
    list_csv_read(FILE_NOTE, list, item_csv_readField);
    list_csv_read(FILE_TASK, list, item_csv_readField);
    list_csv_read(FILE_EVENT, list, item_csv_readField);
}

item_type main_whichItemType() {
    while (1) {
        readInput("Which item type? (note, task, event): ");
        char input[sizeof(inputBuffer)];
        snprintf(input, sizeof(inputBuffer), "%s", inputBuffer);
        strupr(input);
        if      (!strcmp(input, "NOTE"))  return NOTE;
        else if (!strcmp(input, "TASK"))  return TASK;
        else if (!strcmp(input, "EVENT")) return EVENT;
        printf("Invalid type\n");
    }
}
