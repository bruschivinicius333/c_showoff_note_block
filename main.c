#include <stdio.h>
#include <stdlib.h>

#include "include/List.h"
#include "include/main_functions.h"

int main() {

    List *mainList = list_create();

    main_retrieveFromCsv(&mainList);

    while(1) {

        menuOptions menuOption = 0;

        while(1) {

            printf("\nTHE BLOCK:\n");
            printf("1. Create:\n");
            printf("2. Read\n");
            printf("3. Delete\n");
            printf("4. Statistics\n");
            printf("5. Exit\n");
            
            menuOption = readInt();

            if(menuOption) break;
        }

        item_type which = 0;

        switch(menuOption) {
            case CREATE:
                which = main_whichItemType();
                main_insertItem(&mainList, which);
                break;
            case READ:
                which = main_whichItemType();
                main_readItem(&mainList, which);
                break;
            case DELETE:
                which = main_whichItemType();
                main_deleteItem(&mainList, which);
                break;
            case STATISTICS:
                main_statistics(&mainList);
                break;
            case EXIT:
                main_exit(&mainList);
                break;

        }

    }


    return 0;
}