# PracticaStrings_DPS
Practica 1 del curso 2026/2027 de Diseño y Programación Seguras

***PARTE I — Auditoría de seguridad***

**1) Compilación Inicial:**
     
- **Comando utilizado para realizar la 1ª compilación:**  gcc -std=c11 -Wall -Wextra -Wpedantic exampleStrings.c -o exampleStrings
- **Comando utilizado para compilar el programa modificado**  gcc -std=c11 -Wall -Wextra -Wpedantic exampleStrings_fixed.c -o exampleStrings_fixed
- **Comando utilizado para ejecutar el programa modificado:**  ./exampleStrings_fixed hola adios
  
- **Compilador Utilizado** -> `gcc` (GNU Compiler Collection)
- **Versión** -> gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
- **Estándar Utilizado** -> -std=c11
- **Opciones de compilación** ->
  - **`-Wall`** → activa un conjunto amplio de advertencias.
  - **`-Wextra`** → activa advertencias adicionales.
  - **`-Wpedantic`** → avisa sobre construcciones que no cumplen estrictamente el estándar seleccionado.
  - **`exampleStrings_fixed.c`** → archivo fuente que se compila.
  - **`-o exampleStrings_fixed`** → nombre del ejecutable generado.
  - **Errores y Warnings obtenidos al realizar la 1ª Compilación**:
  <img width="1396" height="880" alt="image" src="https://github.com/user-attachments/assets/328434f1-1031-48f6-a715-14007614fa3e" />
  - **Warnings obtenidos al arreglar el error de Raw String de C++**:
  <img width="1515" height="446" alt="image" src="https://github.com/user-attachments/assets/f172103b-4825-488e-930e-65a62ab545e1" />

**2) Solución de errores**

2.1) FRAGMENTOS DE CÓDIGO QUE NO CUMPLEN LA NORMATIVA SEI CERT

```c
1) // Código erróneo: 
char *ptr_char  = "new string literal"; // Línea 67
ptr_char [0] = 'N'; // Línea 101
// Regla/s que incumple: STR30-C: Do not attempt to modify String literals.
// Motivo: ptr_char apunta a un literal de cadena y posteriormente se intenta modificar en la linea 101.
// Solución:
char ptr_char[]  = "new string literal";
ptr_char [0] = 'N';
```

```c
2) // Código erróneo: 
// char analitic1[size_array1]="аналитик";  //Linea 71
// char analitic2[size_array2]="аналитик";  //Linea 72
char analitic3[100]="аналитик";             //Linea 73
// Regla/s que incumple: STR11-C : Do not specify the bound of a character array initialized with a string literal 
// Solución:
char analitic3[]="аналитик"; 
```

```c
3) // Código erróneo:
strncpy(array3, array5, sizeof(array3)); // Línea 97
strncpy(array4, array3, strlen(array3)); // Línea 98
// Regla/s que incumple: STR31-C: Guarantee that storage for strings has sufficient space for character data and the null terminator y
// STR32-C. Do not pass a non-null-terminated character sequence to a library function that expects a string.
// Motivo: array3 tiene 16 bytes, pero strncpy() copia 16 caracteres, sin garantizar espacio para el terminador '\0'. 
// Posteriormente se utiliza strlen(array3), que requiere una cadena terminada en '\0'.
// Solución:
strncpy(array3, array5, sizeof(array3)-1);
array3[sizeof(array3) - 1] = '\0';

strncpy(array4, array3, sizeof(array4) - 1);
array4[sizeof(array4) - 1] = '\0';
```

```c
4) // Código erróneo: 
gets(response); //Linea 51
// Regla/s que incumple: MSC24-C. Do not use deprecated or obsolescent functions
// Solución:
fgets(response, sizeof(response), stdin);
```

```c
5) // Código erróneo: 
strcpy(key, argv[1]); //Linea 78
// Regla/s que incumple: STR35-C. Do not copy data from an unbounded source to a fixed length array
// Motivo: La función strcpy() no recibe información sobre el tamaño de key, por lo que una entrada suficientemente larga
// puede provocar un buffer overflow.
// Solución:
if (snprintf(key, sizeof(key), "%s = %s", argv[1], argv[2]) >= (int)sizeof(key)) {
        fprintf(stderr,"snprintf() error - Key too long\n");
        return 1;
}
```

2.2) OTRAS CORRECCIONES Y MEJORAS
```c
  - 1) // Código erróneo: 
        const char* s1 = R"foo(
        Hello
        World
        )foo"; //Lineas 22 a 25
        // Motivo: Se intenta crear la cadena utilizando un Raw String de C++, algo que no está aceptado por el estándar C11
        // Consecuencia: Error de compilación
        // Solución:
        const char* s1 = "\nHello\nWorld\n";
```

```c
  - 2) // Código erróneo: 
        const char *get_dirname(const char *pathname) {
          char *slash;
          slash = strrchr(pathname, '/');
          if (slash) {
            *slash = '\0'; /* Undefined behavior */
          }
          return pathname;
        } //lineas 37 a 44
        // Motivo: Se intenta alterar una variable constante
        // Solución:
        Modificar la función utilizando la función getcwd() para obtener el directorio actual, añadiendo además la librería unistd.h
```

```c
  - 3)  // Contexto: Se añade una comprobación del número de argumentos (3) para que al programa funcione de forma correcta.
        // Solución:
        if(argc != 3) {
          printf("Usage: %s <key> <value>\n", argv[0]);
          return 1;
        }
```

```c

  - 4)  // Contexto: Se añade una comprobación más correcta en la función get_y_or_n, que tenga en cuenta mayúsculas, minúsculas y
        // que al meterse 5 veces seguidas un valor distinto a Y,y,N,n, se termine igualmente el programa (linea 47 a 57)
        // Solución: Crear un bucle do-while y un contador para los intentos fallidos
        
```

```c

  - 5)  // Contexto: Se agrupan las llamadas a la función printf de las líneas 87 a 90 en 2 para realizar menos llamadas a la función.
        // Comentario: Se podría hacer también con las funciones puts de las líneas 92 a 95,
        // ya que al utilizar la función puts, se incluye un salto de línea de forma automática
        
```

```c

  - 6)  // Lineas comentadas que no se utilizan: 22, 28-34, 38-44, 63, 67-72, 83
        
```
**3) EJEMPLO DE EJECUCIÓN**
<img width="1515" height="1008" alt="Captura desde 2026-10-02 00-32-28" src="https://github.com/user-attachments/assets/e64e9a41-ebbf-484c-b42d-52f988e22970" />
