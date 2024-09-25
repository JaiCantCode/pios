

void putc(int data) {
   int *muio;
   muio = 0x3f215040;
   *muio = data;
}
