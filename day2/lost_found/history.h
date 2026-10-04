#ifndef HISTORY_H
#define HISTORY_H

#include <stddef.h>

typedef struct HistoryNode {
	char *message;
	struct HistoryNode *next;
} HistoryNode;

typedef struct {
	HistoryNode *head;
	size_t count;
} History;

void history_init(History *history);
int history_add(History *history, const char *message);
void history_print(const History *history);
void history_destroy(History *history);

#endif
