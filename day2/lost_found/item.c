#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "item.h"

static char *duplicate_string(const char *source) {
	size_t length = strlen(source);

	char *copy = malloc((length + 1) * sizeof(*copy));

	if (copy == NULL) {
		return NULL;
	}

	memcpy(copy, source, length + 1);

	return copy;
}

Item *item_create (
	int id,
	const char *name,
	const char *description,
	const char *location
) 
{
	Item *item = malloc(sizeof(*item));

	if (item == NULL) {
		return NULL;
	}

	item->id = id;
	item->claimed = 0;
	item->name = NULL;
	item->description = NULL;
	item->location = NULL;

	item->name = duplicate_string(name);
	item->description = duplicate_string(description);
	item->location = duplicate_string(location);

	if (item->name == NULL ||
		item->description == NULL ||
		item->location == NULL)
	{
		item_destroy(item);
		return NULL;			
	}

	return item;
}

void item_destroy(Item *item) {
	if (item == NULL) {
		return;
	}

	free(item->name);
	free(item->description);
	free(item->location);
	free(item);
}

void item_print(const Item *item) {
	printf("\n");
	printf("ID:          %d\n", item->id);
	printf("Name:        %s\n", item->name);
	printf("Description: %s\n", item->description);
	printf("Location:    %s\n", item->location);
	printf("Status:      %s\n", item->claimed ? "Claimed" : "Unclaimed");
}













