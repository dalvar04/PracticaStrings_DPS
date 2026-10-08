#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int resultado;

    printf("=== MSC24-C: prueba original ===\n");

    resultado = system(
        "python3 -c \"print('A' * 100)\" | "
        "./exampleStrings_asan hola mundo"
    );

    if (resultado != 0) {
        printf("ORIGINAL: se detecto un fallo.\n");
    } else {
        printf("ORIGINAL: no se detecto un fallo.\n");
    }

    printf("\n=== MSC24-C: prueba corregida ===\n");

    resultado = system(
        "python3 -c \"print('A' * 100)\" | "
        "./exampleStrings_fixed_asan hola mundo"
    );

    if (resultado != 0) {
        printf("FIXED: se detecto un fallo.\n");
    } else {
        printf("FIXED: ejecucion correcta.\n");
    }

    return 0;
}