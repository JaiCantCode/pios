//#include <stdio.h>
//#include "generalTester.c"

char glbl[128];
char huge_array[8192];


//unsigned long get_timer_count();
//void wait_msec();
//void wait_cycles();
//void testprint();

void kernel_main() {
   fatInit();

   //testprint();
   //espPrintfTest();
   /*
   unsigned long tcr = get_timer_count();
   extern int __bss_start, __bss_end;
   char *begin_bss, *end_bss;
   
   begin_bss = (char*)&__bss_start;
   end_bss = (char*)&__bss_end;

   tcr = get_timer_count();
   wait_msec(1);
   tcr = get_timer_count();

   for(begin_bss; begin_bss < end_bss; begin_bss++) {
      *begin_bss = 0xff;
   }
   */
}

/*
unsigned long get_timer_count() {
   unsigned long *timer_count_register = (long unsigned int*)0x3f003004;
   return *timer_count_register;
}

void wait_msec(int m) {
   unsigned long tmp = get_timer_count();
   while(1) {
      if(get_timer_count() >= tmp + (m*1000)) break;
   }
}

void wait_cycles(int t) {
   unsigned long tmp = get_timer_count();
   while(1){
      if(get_timer_count() >= tmp + t) break;
   }
}
*/
