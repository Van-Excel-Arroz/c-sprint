#include <stdio.h>
#include <stdlib.h>

#include "item_list.h"

#define INITIAL_CAPACITY 4

void item_list_init(ItemList *list) {
	list->items = NULL;
	list->size = 0;
	list->capacity = 0;
}

static int item_list_grow(ItemList *list) {
	size_t new_capacity;

	if (list->capacity == 0) {
		new_capacity = INITIAL_CAPACITY;
	} else {
		new_capacity = list->capacity * 2;
	}

	Item **new_items = realloc(
		list->items,
		new_capacity * sizeof(*new_items)
	);

	if (new_items == NULL) {
		return 0;
	}

	list->items = new_items;
	list->capacity = new_capacity;
	
	return 1;
}

int item_list_add(ItemList *list, Item *item) {
	if (list->size == list->capacity) {
		if (!item_list_grow(list)) {
			return 0;
		}
	}

	list->items[list->size] = item;
	list->size++;
	
	return 1;
}

Item *item_list_find_by_id(ItemList *list, int id) {
	for (size_t i = 0; list->size > i; i++) {
		if (list->items[i]->id == id) {
			return list->items[i];
		}
	}

	return NULL;
}

void item_list_print(const ItemList *list) {
	if (list->size == 0) {
		printf("\nNo items found.\n");
		return;
	}

	for (size_t i = 0; list->size > i; i++) {
		item_print(list->items[i]);
	}
}

void item_list_sort(
	ItemList *list,
	int (*compare) (const Item *, const Item *)
) {
	for (size_t i = 0; list->size > i; i++) {
		for (size_t j = i + 1; list->size > j; j++) {
			if (compare(
				list->items[i],
				list->items[j]
			) > 0) {
				Item *temp = list->items[i];
				list->items[i] = list->items[j];
				list->items[j] = temp;
			}
		}
	}
}

void item_list_destroy(ItemList *list) {
	if (list == NULL) {
		return;
	}

	for (size_t i = 0; list->size > i; i++) {
		item_destroy(list->items[i]);
	}

	free(list->items);
	list->items = NULL;
	list->size = 0;
	list->capacity = 0;
}
