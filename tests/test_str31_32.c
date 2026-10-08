#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int resultado;

    printf("=== STR31-C / STR32-C: prueba original ===\n");

    resultado = system("./exampleStrings_asan hola mundo");

    if (resultado != 0) {
        printf("ORIGINAL: se detecto un fallo.\n");
    } else {
        printf("ORIGINAL: no se detecto un fallo.\n");
    }

    printf("\n=== STR31-C / STR32-C: prueba corregida ===\n");

    resultado = system("./exampleStrings_fixed_asan hola mundo");

    if (resultado != 0) {
        printf("FIXED: se detecto un fallo.\n");
    } else {
        printf("FIXED: ejecucion correcta.\n");
    }

    return 0;
}