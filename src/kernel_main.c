//#include <stdio.h>
//#include "serial.c"
//#include "rprintf.c"
#include "generalTester.c"

char glbl[128];
char huge_array[8192];


unsigned long get_timer_count();
void wait_one_ms();
//void espPrintfTest();

void kernel_main() {
   espPrintfTest();
   unsigned long tcr = get_timer_count();
   extern int __bss_start, __bss_end;
   char *begin_bss, *end_bss;

   begin_bss = (char*)&__bss_start;
   end_bss = (char*)&__bss_end;

   tcr = get_timer_count();
   wait_one_ms();
   tcr = get_timer_count();

   for(begin_bss; begin_bss < end_bss; begin_bss++) {
      *begin_bss = 0xff;
   }
}


unsigned long get_timer_count() {
   unsigned long *timer_count_register = 0x3f003004;
   return *timer_count_register;
}

void wait_one_ms() {
   unsigned long tmp = get_timer_count();
   while(1) {
      if(get_timer_count() >= tmp + 1000) break;
   }
}
/*
void espPrintfTest() {
   char ooga[] = "Hello World!";
   esp_printf(putc, "%s", ooga);
}
*/


