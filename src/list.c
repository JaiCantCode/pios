#include <stdio.h>
#include "list.h"

int main() {
   
   struct list_element head = {NULL, 0, NULL};
   struct list_element a = {NULL, 1, NULL};
   struct list_element b = {NULL, 2, NULL};
   struct list_element c = {NULL, 3, NULL};
   struct list_element d = {NULL, 4, NULL};

   list_add(&head, &a);
   list_add(&head, &b);
   list_add(&head, &c);
   list_add(&head, &d);
   /*
   printf("\nList: %d, %d, %d, %d, %d", head.data, a.data, b.data, c.data, d.data);
   printf("\nList: ");
   for(struct list_element *i = &head; i != NULL; i = i->next) {
      printf("%d, ", i->data);
   }
   */
   list_remove(&b); //Testing remove method: removed list element b
   /*   
   printf("\nRemoved element b\nList: ");
   for(struct list_element *i = &head; i != NULL; i = i->next) {
      printf("%d, ", i->data);
   }
   printf("\n");
   */
   return 0;
}


void list_add(struct list_element *list_head, struct list_element *new_element){
   if(new_element->prev != NULL) return; // If the new element is in the middle or end of another list 
   if(list_head->next != NULL) {
      list_add(list_head->next, new_element); // Iterates through the list to get the end element
      return;
   }
   list_head->next = new_element;
   new_element->prev = list_head;
}

void list_remove(struct list_element *rem_element){
   if(rem_element->next == NULL && rem_element->prev == NULL) return; // If the element is not attached to anything
   if(rem_element->next == NULL){ // If the element is the last in the list
      rem_element->prev->next = NULL;
      rem_element->prev == NULL;
      return;
   }
   if(rem_element->prev == NULL){ // If the element is the head of the list
      rem_element->next->prev = NULL;
      rem_element->next == NULL;
      return;
   }
   // If the element is in the middle of the list
   rem_element->prev->next = rem_element->next;
   rem_element->next->prev = rem_element->prev;
   rem_element->prev = NULL;
   rem_element->next = NULL;
}

