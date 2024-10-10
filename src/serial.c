

void putc(int data) {
   int *muio;
   muio = 0x3f215040;
   *muio = data;
}

void testprint() {
   char oogabooga[] = "Hello World! Ooga Booga";
   esp_printf(putc, "%s", oogabooga);
}
