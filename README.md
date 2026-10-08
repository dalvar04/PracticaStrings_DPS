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
  - **`exampleStrings.c | exampleStrings_fixed.c`** → archivo fuente que se compila.
  - **`-o exampleStrings | exampleStrings_fixed`** → nombre del ejecutable generado.
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

  - 6)  // Líneas comentadas que no se utilizan: 22, 28-34, 38-44, 63, 67-72, 83
        
```
**3) EJEMPLO DE EJECUCIÓN**

<img width="1515" height="1008" alt="Captura desde 2026-10-02 00-32-28" src="https://github.com/user-attachments/assets/e64e9a41-ebbf-484c-b42d-52f988e22970" />







***PARTE II — Tests y verificación***

**1) Diseño de pruebas**

Para esta segunda parte se han seleccionado cuatro problemas diferentes de la auditoría realizada en la Parte I:

- STR30-C — Do not attempt to modify string literals.

- STR35-C — Do not copy data from an unbounded source to a fixed length array.

- STR31-C / STR32-C — Garantizar espacio suficiente para cadenas y no pasar secuencias no terminadas en '\0' a funciones que esperan cadenas.

- MSC24-C — Do not use deprecated or obsolescent functions.

Se han utilizado diferentes técnicas de verificación, principalmente análisis estático y pruebas funcionales con casos límite. Para detectar errores de memoria se ha utilizado AddressSanitizer.

1.1) STR30-C: Do not attempt to modify String literals.
   - Problema: ptr_char apunta a un literal de cadena y posteriormente se intenta modificar en la linea 101
   - Test o entrada:
     -        gcc -std=c11 -Wall -Wextra -Wpedantic -fanalyzer exampleStrings.c -o exampleStrings
     -       ./exampleStrings_fixed cadena1 cadena2
   - Técnica: Añadir al comando de compilación la función -fanalyzer, para realizar un análisis estático de código
   - Código original:
     
          - Línea 67 (exampleStrings.c):  char *ptr_char  = "new string literal"; 
          - Línea 101 (exampleStrings.c): ptr_char [0] = 'N';
     
   - Resultado de la compilación con código original:

   <img width="531" height="91" alt="Captura desde 2026-10-08 15-33-46" src="https://github.com/user-attachments/assets/82b2ba18-5271-4a4e-9aa5-aa0f801478e3" />
   

   - Código corregido:
     
          - Línea 70 (exampleStrings_fixed.c): char ptr_char [] = "new string literal"; 
          - Línea 98 (exampleStrings_fixed.c): ptr_char [0] = 'N';
          - Línea 99 (exampleStrings_fixed.c): printf ("%s\n",ptr_char);
     
   - Resultado de la compilación con código corregido:

     <img width="1585" height="320" alt="Captura desde 2026-10-08 15-47-00" src="https://github.com/user-attachments/assets/85405c54-db48-4e73-ae6a-29cebee3e4e8" />
     

   ** NOTA: A este código se le añade un printf para mostrar el contenido de la cadena, ya que sin él se obtiene un Warning:
   
   <img width="1585" height="121" alt="Captura desde 2026-10-08 15-48-06" src="https://github.com/user-attachments/assets/f66bd6f7-66b6-4a1b-907d-688a5e99429f" />
   


1.2) STR35-C: Do not copy data from an unbounded source to a fixed length array


   - Problema: La función strcpy() no recibe información sobre el tamaño de key, por lo que una entrada suficientemente larga 
          puede provocar un buffer overflow.
   - Test o entrada:
          
               - gcc -Wall -Wextra -g -fsanitize=address,undefined [archivo].c -o e[archivo]_asan
               - ./[archivo] " ,/[archivo]_asan "$(python3 -c "print('A' * 511)")" "$(python3 -c "print('B' * 511)")"
           
   - Técnica: Utilización de AddressSanitizer y UndefinedBehaviorSanitizer en la compilación y entradas tanto normales como de situaciones límite
   - Código original:
          
               
                - Línea 78 (exampleStrings.c):  strcpy(key, argv[1]);
               
   - Código corregido:
              
               - Línea 75 (exampleStrings_fixed.c): if (snprintf(key, sizeof(key), "%s = %s", argv[1], argv[2]) >= (int)sizeof(key)) {
               - Línea 76 (exampleStrings_fixed.c):       fprintf(stderr,"snprintf() error - Key too long\n");
               - Línea 77 (exampleStrings_fixed.c):       return 1;
               
   - Comparación entre código anterior y código corregido:

     
     <img width="1570" height="1104" alt="image" src="https://github.com/user-attachments/assets/4ffc9665-57c5-4ed9-9496-2fb61eadb07e" />

     

  1.3) STR31-C: Guarantee that storage for strings has sufficient space for character data and the null terminator y
       STR32-C. Do not pass a non-null-terminated character sequence to a library function that expects a string.
       
   - Problema: array3 tiene 16 bytes, pero strncpy() copia 16 caracteres, sin garantizar espacio para el terminador '\0'. 
       Posteriormente se utiliza strlen(array3), que requiere una cadena terminada en '\0'.
   - Test o entrada:
          
               - gcc -Wall -Wextra -g -fsanitize=address,undefined [archivo]_fixed.c -o [archivo]_asan
               - ./[archivo]_str**" ,/[archivo]_asan "$(python3 -c "print('A' * 511)")" "$(python3 -c "print('B' * 511)")"
           
   - Técnica: Utilización de AddressSanitizer y UndefinedBehaviorSanitizer en la compilación y entradas tanto normales como de situaciones límite
   - Código original:
          
               `
                - Línea 97 (exampleStrings.c):  strncpy(array3, array5, sizeof(array3));
                - Línea 98 (exampleStrings.c):  strncpy(array4, array3, sizeof(array3));
               
   - Código corregido:
            
               
               - Línea 91 (exampleStrings_fixed.c): strncpy(array3, array5, sizeof(array3)-1)
               - Línea 92 (exampleStrings_fixed.c): array3[sizeof(array3) - 1] = '\0';

               - Línea 95 (exampleStrings_fixed.c): strncpy(array4, array3, sizeof(array4) - 1);
               - Línea 96 (exampleStrings_fixed.c): array4[sizeof(array4) - 1] = '\0';
               
               
   - Comparación entre código anterior y código corregido:
     <img width="1570" height="942" alt="image" src="https://github.com/user-attachments/assets/5820b1f3-7ade-4b23-8038-aef3dae55755" />
     <img width="1570" height="602" alt="image" src="https://github.com/user-attachments/assets/edf5fa2b-c7bb-4d42-b962-14eb4834f143" />

     

  1.4) MSC24-C. Do not use deprecated or obsolescent functions
     
   - Problema: array3 tiene 16 bytes, pero strncpy() copia 16 caracteres, sin garantizar espacio para el terminador '\0'. 
       Posteriormente se utiliza strlen(array3), que requiere una cadena terminada en '\0'.
   - Test o entrada:
          
               - gcc -Wall -Wextra -g -fsanitize=address,undefined [archivo]_fixed.c -o [archivo]_asan
               - ./[archivo]_str**" ,/[archivo]_asan "$(python3 -c "print('A' * 511)")" "$(python3 -c "print('B' * 511)")"
           
   - Técnica: Utilización de AddressSanitizer y UndefinedBehaviorSanitizer en la compilación y entradas tanto normales como de situaciones límite
   - Código original:
          
               
                - Línea 48 (exampleStrings.c):  gets(response);
               
   - Código corregido:
               
               - Línea 32 (exampleStrings_fixed.c): fgets(response, sizeof(response), stdin);
               
   - Comparación entre código anterior y código corregido:

  
       <img width="1570" height="488" alt="image" src="https://github.com/user-attachments/assets/f063fddb-725e-4bd0-be42-8884bc2baa2a" />

  
***PARTE III — Declaración de uso de IA***

- **Herramienta utilizada: ChatGPT (GPT-5.6 Luna).** 
- **Tareas para las que se utilizó**
     - Identificación y explicación de problemas relacionados con las reglas CERT C seleccionadas.
     - Correcciones en las mejoras de código propuestas
     - Explicación del uso de AddressSanitizer (-fsanitize=address,undefined) y de system() para automatizar las pruebas.
     - Generación de casos de pruebas, incluyendo ejemplos de casos de entrada límite
     - Mejoras en el README.md (ortográficas, correcciones en el código Markdown...)
- **Cómo se verificaron sus respuestas**
     - Las propuestas realizadas se comprobaron compilando y ejecutando los programas en el entorno de trabajo,
       mediante la ejecución de la misma entrada para los archivos original y modificado
- **Ejemplo relevante de utilización:** Para comprobar STR35-C, se solicitó ayuda para diseñar un caso límite que provocase un desbordamiento del buffer key.
- Se utilizó la siguiente entrada: ./exampleStrings_asan "$(python3 -c "print('A' * 511)")" "$(python3 -c "print('B' * 511)")"
- **Tiempo necesario para realizar este ejercicio: Aproximadamente 15 horas entre ambas partes**       
