#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include <stddef.h>

#include "item.h"

typedef struct {
	Item **items;
	size_t size;
	size_t capacity;
} ItemList;

void item_list_init(ItemList *list);

int item_list_add(ItemList *list, Item *item);

Item *item_list_find_by_id(ItemList *list, int id);

void item_list_print(const ItemList *list);

void item_list_sort(ItemList *list, int (*compare)(const Item *, const Item *));

void item_list_destroy(ItemList *list);

#endif 
