/*\
 *
 * This file is what I am going to use to test any addtional add on the pios repo
 *
\*/

#include "rprintf.c"
#include "serial.c"

int main() {return 0;}

void espPrintfTest() {
   char oogabooga[] = "Hello World! Ooga Booga";
   esp_printf(putc, "%s", oogabooga);
}
