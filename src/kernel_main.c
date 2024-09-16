#include <stdio.h>

char glbl[128];

char huge_array[8192];

void kernel_main() {

    extern int __bss_start, __bss_end;
    char *begin_bss, *end_bss;

    begin_bss = &__bss_start;
    end_bss = &__bss_end;

    for(begin_bss; begin_bss =< end_bss; begin_bss++) {
        *begin_bss = 0;
    }
}
