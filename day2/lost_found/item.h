#ifndef ITEM_H
#define ITEM_H

typedef struct Item {
	int id;
	int claimed;
	char *name;
	char *description;
	char *location;
} Item;

Item *item_create(
	int id,
	const char *name,
	const char *description,
	const char *location	
);

void item_destroy(Item *item);

void item_print(const Item *item);	

#endif


