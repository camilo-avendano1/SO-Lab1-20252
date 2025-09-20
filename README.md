# Programa Reverse

## Información del Proyecto

**Participantes:**

- Juan Camilo Avendaño Rodriguez- ID 1193585383
- Jose Fernando Waldo Rojas - ID: 1004807096

**Fecha:** Septiembre 2025  
**Curso:** Sistemas Operativos

## Descripción

El programa `reverse` es una utilidad que lee líneas de texto desde un archivo o entrada estándar y las imprime en orden inverso. Es decir, la última línea leída se imprime primero, y la primera línea leída se imprime al final.

## Funcionalidades

El programa puede ejecutarse de tres formas diferentes:

1. **Sin argumentos**: Lee desde entrada estándar (teclado) y escribe a salida estándar (pantalla)
2. **Un argumento**: Lee desde archivo especificado y escribe a salida estándar
3. **Dos argumentos**: Lee desde archivo de entrada y escribe a archivo de salida

## Compilación

Para compilar el programa, ejecute el siguiente comando en la terminal:

```bash
gcc -o reverse reverse.c
```

## Formas de Ejecución

### 1. Lectura desde entrada estándar

```bash
./reverse
```

El usuario puede ingresar líneas de texto manualmente. Para terminar la entrada, presione `Ctrl+D` (EOF).

### 2. Lectura desde archivo

```bash
./reverse input.txt
```

Lee el contenido del archivo `input.txt` y muestra las líneas en orden inverso en la pantalla.

### 3. Lectura y escritura de archivos

```bash
./reverse input.txt output.txt
```

Lee el contenido de `input.txt` y escribe las líneas en orden inverso al archivo `output.txt`.

## Ejemplo de Uso

Si tenemos un archivo `entrada.txt` con el siguiente contenido:

```
primera línea
segunda línea
tercera línea
cuarta línea
```

Al ejecutar (CTRL + D):

```bash
./reverse entrada.txt
```

La salida será:

```
cuarta línea
tercera línea
segunda línea
primera línea
```

## Arquitectura del Programa

### Estructura de Datos Utilizada

El programa utiliza una **lista enlazada** para almacenar las líneas leídas:

```c
typedef struct Node {
    char *line;        // Puntero a la línea de texto
    struct Node *next; // Puntero al siguiente nodo
} Node;
```

Esta estructura permite:

- Almacenar líneas de cualquier longitud
- Agregar elementos dinámicamente
- Invertir el orden fácilmente insertando al inicio

### Flujo de Ejecución Paso a Paso

1. **Inicialización**:

   - Se declaran variables para archivos de entrada y salida
   - Se inicializa la lista enlazada como vacía (`head = NULL`)

2. **Procesamiento de argumentos**:

   - Se verifica el número de argumentos de línea de comandos
   - Se valida que el archivo de entrada y salida sean diferentes (si aplica)
   - Se abren los archivos correspondientes

3. **Lectura de datos**:

   - Se lee línea por línea usando `getline()`
   - Cada línea se almacena en un nuevo nodo de la lista
   - Los nodos se insertan al inicio de la lista (inversión automática)

4. **Escritura de resultados**:

   - Se recorre la lista desde el inicio
   - Se imprime cada línea en el archivo/pantalla de salida
   - Se libera la memoria de cada nodo procesado

5. **Limpieza**:
   - Se cierran los archivos abiertos
   - Se libera toda la memoria reservada

## Funciones Clave Utilizadas

### Funciones del Sistema

#### `getline()`

```c
ssize_t getline(char **lineptr, size_t *n, FILE *stream);
```

- **Propósito**: Lee una línea completa desde un archivo, incluyendo el carácter de nueva línea
- **Ventaja**: Maneja automáticamente líneas de cualquier longitud, reservando memoria dinámicamente
- **Uso en el programa**: Leer cada línea del archivo de entrada sin límites de tamaño

#### `fopen()` y `fclose()`

```c
FILE *fopen(const char *pathname, const char *mode);
int fclose(FILE *stream);
```

- **Propósito**: Abrir y cerrar archivos respectivamente
- **Modos utilizados**:
  - `"r"`: Lectura (archivo de entrada)
  - `"w"`: Escritura (archivo de salida)
- **Uso en el programa**: Gestionar archivos de entrada y salida según los argumentos

#### `malloc()` y `free()`

```c
void *malloc(size_t size);
void free(void *ptr);
```

- **Propósito**: Reservar y liberar memoria dinámica
- **Uso en el programa**:
  - Crear nodos de la lista enlazada
  - Almacenar copias de las líneas leídas
  - Evitar fugas de memoria liberando todo lo reservado

#### `fprintf()`

```c
int fprintf(FILE *stream, const char *format, ...);
```

- **Propósito**: Escribir texto formateado a un archivo específico
- **Streams utilizados**:
  - `stdout`: Salida estándar (pantalla)
  - `stderr`: Error estándar (mensajes de error)
  - Archivos abiertos con `fopen()`

### Funciones Personalizadas

#### `add_line()`

```c
Node* add_line(Node *head, char *line);
```

- **Propósito**: Agregar una nueva línea al inicio de la lista enlazada
- **Funcionamiento**:
  1. Reserva memoria para un nuevo nodo
  2. Copia la línea recibida
  3. Conecta el nuevo nodo al inicio de la lista
  4. Retorna el nuevo inicio de la lista
- **Resultado**: Inversión automática del orden de las líneas

#### `print_and_free_list()`

```c
void print_and_free_list(Node *head, FILE *output);
```

- **Propósito**: Imprimir todas las líneas de la lista y liberar memoria
- **Funcionamiento**:
  1. Recorre la lista desde el inicio
  2. Imprime cada línea en el archivo de salida
  3. Libera la memoria del nodo y su línea
  4. Avanza al siguiente nodo
- **Resultado**: Salida en orden inverso y limpieza de memoria

## Manejo de Errores

El programa implementa un robusto manejo de errores para los siguientes casos:

1. **Archivo de entrada igual al de salida**:

   ```
   El archivo de entrada y salida deben diferir
   ```

2. **Error al abrir archivos**:

   ```
   error: cannot open file 'nombre_archivo'
   ```

3. **Fallo en reserva de memoria**:

   ```
   malloc failed
   ```

4. **Demasiados argumentos**:
   ```
   usage: reverse <input> <output>
   ```

Todos los errores se imprimen a `stderr` y el programa termina con código de salida 1.

## Consideraciones de Implementación

### Manejo de Memoria

- Se utiliza memoria dinámica para manejar archivos de cualquier tamaño
- Cada línea se almacena independientemente sin límite de longitud
- Se libera toda la memoria reservada antes de terminar

### Eficiencia

- La lista enlazada permite inserción O(1) al inicio
- La impresión es O(n) recorriendo una vez la lista
- El uso de memoria es proporcional al tamaño del archivo

## Pruebas Recomendadas

Para verificar el correcto funcionamiento del programa, se recomienda probar:

1. **Casos básicos**:

   - Archivo pequeño con pocas líneas
   - Archivo vacío
   - Entrada desde teclado

2. **Casos límite**:

   - Archivos muy grandes
   - Líneas muy largas
   - Archivos con caracteres especiales

3. **Casos de error**:

   - Archivos inexistentes
   - Archivos de entrada y salida idénticos
   - Permisos insuficientes

4. **Casos extremos**:
   - Archivo de una sola línea
   - Líneas vacías
   - Archivo solo con espacios en blanco

#
