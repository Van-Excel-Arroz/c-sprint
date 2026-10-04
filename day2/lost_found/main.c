#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "item_list.h"
#include "history.h"
#include "input.h"

static int compare_by_id(
    const Item *a,
    const Item *b
)
{
    if (a->id < b->id) {
        return -1;
    }

    if (a->id > b->id) {
        return 1;
    }

    return 0;
}

static int compare_by_name(
    const Item *a,
    const Item *b
)
{
    return strcmp(a->name, b->name);
}

static void print_menu(void)
{
    printf("\n");
    printf("========================================\n");
    printf("          LOST & FOUND MANAGER\n");
    printf("========================================\n");
    printf("1. Add item\n");
    printf("2. List items\n");
    printf("3. Search item by ID\n");
    printf("4. Claim item\n");
    printf("5. Show history\n");
    printf("6. Sort by ID\n");
    printf("7. Sort by name\n");
    printf("0. Exit\n");
    printf("========================================\n");
    printf("Choose: ");
}

static void add_item(
    ItemList *items,
    History *history,
    int *next_id
)
{
    char name[128];
    char description[256];
    char location[128];

    printf("\nItem name: ");
    read_line(
        name,
        sizeof(name)
    );

    printf("Description: ");
    read_line(
        description,
        sizeof(description)
    );

    printf("Location found: ");
    read_line(
        location,
        sizeof(location)
    );

    Item *item = item_create(
        *next_id,
        name,
        description,
        location
    );

    if (item == NULL) {
        printf("Failed to allocate memory.\n");
        return;
    }

    if (!item_list_add(items, item)) {
        printf("Failed to add item.\n");

        item_destroy(item);

        return;
    }

    char message[256];

    snprintf(
        message,
        sizeof(message),
        "Added item #%d: %s",
        item->id,
        item->name
    );

    history_add(
        history,
        message
    );

    printf(
        "\nItem added successfully. ID = %d\n",
        *next_id
    );

    (*next_id)++;
}

static void search_item(ItemList *items)
{
    printf("\nEnter item ID: ");

    int id = read_int();

    Item *item =
        item_list_find_by_id(
            items,
            id
        );

    if (item == NULL) {
        printf("Item not found.\n");
        return;
    }

    item_print(item);
}

static void claim_item(
    ItemList *items,
    History *history
)
{
    printf("\nEnter item ID to claim: ");

    int id = read_int();

    Item *item =
        item_list_find_by_id(
            items,
            id
        );

    if (item == NULL) {
        printf("Item not found.\n");
        return;
    }

    if (item->claimed) {
        printf(
            "This item has already been claimed.\n"
        );

        return;
    }

    item->claimed = 1;

    char message[256];

    snprintf(
        message,
        sizeof(message),
        "Item #%d (%s) was claimed.",
        item->id,
        item->name
    );

    history_add(
        history,
        message
    );

    printf(
        "Item marked as claimed.\n"
    );
}

int main(void)
{
    ItemList items;
    History history;

    item_list_init(&items);
    history_init(&history);

    int next_id = 1;

    int running = 1;

    while (running) {

        print_menu();

        int choice = read_int();

        switch (choice) {

            case 1:
                add_item(
                    &items,
                    &history,
                    &next_id
                );
                break;

            case 2:
                item_list_print(&items);
                break;

            case 3:
                search_item(&items);
                break;

            case 4:
                claim_item(
                    &items,
                    &history
                );
                break;

            case 5:
                history_print(&history);
                break;

            case 6:
                item_list_sort(
                    &items,
                    compare_by_id
                );

                printf(
                    "Sorted by ID.\n"
                );

                break;

            case 7:
                item_list_sort(
                    &items,
                    compare_by_name
                );

                printf(
                    "Sorted by name.\n"
                );

                break;

            case 0:
                running = 0;
                break;

            default:
                printf(
                    "Invalid choice.\n"
                );

                break;
        }
    }

    item_list_destroy(&items);
    history_destroy(&history);

    printf("\nGoodbye!\n");

    return 0;
}
