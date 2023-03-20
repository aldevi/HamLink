#include <stdio.h>
#include <stdlib.h>

void test();

int main(void) {
    printf("Pointeur de test : %p\n", test);
    void (* ptr)() = test;

    // Appel de la fonction
    (*ptr)();
}

void test() {
    printf("test\n");
}