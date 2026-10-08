#include <stdio.h>
#include <stdlib.h>

int main(void) {
    int resultado;

    printf("=== STR35-C: prueba original ===\n");

    resultado = system(
        "./exampleStrings_asan "
        "\"$(python3 -c 'print(\"A\" * 511)')\" "
        "\"$(python3 -c 'print(\"B\" * 511)')\""
    );

    if (resultado != 0) {
        printf("ORIGINAL: se detecto un fallo.\n");
    } else {
        printf("ORIGINAL: no se detecto un fallo.\n");
    }

    printf("\n=== STR35-C: prueba corregida ===\n");

    resultado = system(
        "./exampleStrings_fixed_asan "
        "\"$(python3 -c 'print(\"A\" * 511)')\" "
        "\"$(python3 -c 'print(\"B\" * 511)')\""
    );

    if (resultado != 0) {
        printf("FIXED: el programa rechazo correctamente la entrada.\n");
    } else {
        printf("FIXED: el programa termino correctamente.\n");
    }

    return 0;
}