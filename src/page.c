#include "page.h"
#include <stddef.h>

int page_count = 128;
struct ppage physical_page_array[128]; // 128 pages, each 2mb in length covers 256 megs of memory

int ppage_size = sizeof(physical_page_array[0]); // Gets the size of a singular page. Should be 24

struct ppage *free_page_list;
struct ppage *allocd_list;

void init_pfa_list(void);
struct ppage *allocate_physical_pages(unsigned int npages);
void free_physical_pages(struct ppage *ppage_list);

/*
int main() {
   init_pfa_list();
   allocd_list = allocate_physical_pages(4);
   free_physical_pages(allocd_list);
   return 0;
}
*/

void init_pfa_list(void) {
   for(int i = 0; i < page_count; i++) {
      if(i == 0) {
         physical_page_array[i].next = &physical_page_array[i++];
         physical_page_array[i].prev = NULL;
         free_page_list = &physical_page_array[i];
      }else if(i == page_count--){
         physical_page_array[i].next = NULL;
         physical_page_array[i].prev = &physical_page_array[i--]; 
      }else{
         physical_page_array[i].next = &physical_page_array[i++];
         physical_page_array[i].prev = &physical_page_array[i--];
      }
   }
}

struct ppage *allocate_physical_pages(unsigned int npages) {
   
   if(npages == 0) return NULL;

   struct ppage *tmp = free_page_list;

   for(int i = 1; i < npages; i++) {
      tmp = tmp->next;
   }

   if(tmp == NULL) return NULL;
   
   struct ppage *apgs = free_page_list;
   if(tmp->next == NULL) {
      free_page_list = NULL;
   }else{
      free_page_list = tmp->next;
      free_page_list->prev = NULL;
      tmp->next = NULL;
   }
   return apgs;
}

void free_physical_pages(struct ppage *ppage_list) {
   
   if(ppage_list == NULL) return;

   if(free_page_list == NULL) {
      free_page_list = ppage_list;
      ppage_list = NULL;
      return;
   }

   struct ppage *tmp = ppage_list;
   while(tmp->next != NULL) {
      tmp = tmp->next;
   }

   tmp->next = free_page_list;
   free_page_list->prev = tmp;
   free_page_list = ppage_list;
   ppage_list = NULL;
}


