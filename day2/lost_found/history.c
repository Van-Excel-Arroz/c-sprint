#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "history.h"

static char *duplicate_string(const char *source)
{
    size_t length = strlen(source);

    char *copy = malloc(
        (length + 1) * sizeof(*copy)
    );

    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1);

    return copy;
}

void history_init(History *history)
{
    history->head = NULL;
    history->count = 0;
}

int history_add(
    History *history,
    const char *message
)
{
    HistoryNode *node =
        malloc(sizeof(*node));

    if (node == NULL) {
        return 0;
    }

    node->message = duplicate_string(message);

    if (node->message == NULL) {
        free(node);
        return 0;
    }

    node->next = history->head;

    history->head = node;

    history->count++;

    return 1;
}

void history_print(
    const History *history
)
{
    if (history->head == NULL) {
        printf("\nNo history yet.\n");
        return;
    }

    printf("\n========== HISTORY ==========\n");

    const HistoryNode *current =
        history->head;

    while (current != NULL) {

        printf("- %s\n", current->message);

        current = current->next;
    }
}

void history_destroy(
    History *history
)
{
    HistoryNode *current =
        history->head;

    while (current != NULL) {

        HistoryNode *next =
            current->next;

        free(current->message);
        free(current);

        current = next;
    }

    history->head = NULL;
    history->count = 0;
}
