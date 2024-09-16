#ifndef LIST_H
#define LIST_H

struct list_element {
   struct list_element *next; // Points to the next element
   int data; // Element's stored data
   struct list_element *prev; // Points to the previous element
};

void list_add(struct list_element *list_head, struct list_element *new_element);

void list_remove(struct list_element *rem_element);

#endif
