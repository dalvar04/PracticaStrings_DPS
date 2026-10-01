# PracticaStrings_DPS
Practica 1 del curso 2026/2027 de Diseño y Programación Seguras

***PARTE I — Auditoría de seguridad***

**2) Compilación Inicial:**
     
- **Comando utilizado:**  gcc -std=c11 -Wall -Wextra -Wpedantic exampleStrings_fixed.c -o exampleStrings_fixed
  
- **Compilador Utilizado** -> `gcc` (GNU Compiler Collection)
- **Versión** -> gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0
- **Estándar Utilizado** -> -std=c11
- **Opciones de compilación** ->
  - **`-Wall`** → activa un conjunto amplio de advertencias.
  - **`-Wextra`** → activa advertencias adicionales.
  - **`-Wpedantic`** → avisa sobre construcciones que no cumplen estrictamente el estándar seleccionado.
  - **`exampleStrings_fixed.c`** → archivo fuente que se compila.
  - **`-o exampleStrings_fixed`** → nombre del ejecutable generado.
  - **1ª Compilación**:
  <img width="1396" height="880" alt="image" src="https://github.com/user-attachments/assets/328434f1-1031-48f6-a715-14007614fa3e" />
  - **Compilación tras arreglar error**:
  <img width="1515" height="446" alt="image" src="https://github.com/user-attachments/assets/f172103b-4825-488e-930e-65a62ab545e1" />

**3) Solución de errores**

3.1) ERRORES RELACIONADOS CON EL SEI CERT

```c
1) // Código erróneo: 
char *ptr_char  = "new string literal"; // Línea 67
ptr_char [0] = 'N'; // Línea 101
// Regla/s que incumple: STR30-C: Do not attempt to modify String literals.
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
2) // Código erróneo:
strncpy(array3, array5, sizeof(array3)); // Línea 97
strncpy(array4, array3, strlen(array3)); // Línea 98
// Regla/s que incumple: STR31-C: Guarantee that storage for strings has sufficient space for character data and the null terminator y
// STR32-C. Do not pass a non-null-terminated character sequence to a library function that expects a string (la cadena array5 no termina con un \0)
// Solución:
strncpy(array3, array5, sizeof(array3)-1);
array3[sizeof(array3) - 1] = '\0';

strncpy(array4, array3, sizeof(array4) - 1);
array4[sizeof(array4) - 1] = '\0';
```

```c
2) // Código erróneo: 
gets(response); //Linea 51
// Regla/s que incumple: MSC24-C. Do not use deprecated or obsolescent functions
// Solución:
fgets(response, sizeof(response), stdin
```

```c
2) // Código erróneo: 
strcpy(key, argv[1]); //Linea 78
// Regla/s que incumple: STR35-C. Do not copy data from an unbounded source to a fixed length array
// Solución:
if (snprintf(key, sizeof(key), "%s = %s", argv[1], argv[2]) >= (int)sizeof(key)) {
        fprintf(stderr,"snprintf() error - Key too long\n");
        return 1;
}
```

3.1) OTRAS CORRECCIONES
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
        // que al meterse 5 veces segiuidas un valor distinto a Y,y,N,n, se termine igualmente el programa (linea 47 a 57)
        // Solución: Crear un bucle do-while y un contador para los intentos fallidos
        
```

```c

  - 5)  // Contexto: Se agrupan los printf's de las líneas 87 a 90 en 2 para realizar menos llamadas a la función.
        // Comentario: Se podría hacer tamnién con las funciones puts de las líneas 92 a 95,
        // ya que al utilizar la función puts, se incluye un salto de línea de forma automática
        
```

```c

  - 6)  // Lineas comentadas que no se utilizan: 22, 28-34, 38-44, 63, 67-72, 83
        
```
