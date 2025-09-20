#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estructura para la lista enlazada que almacenará las líneas
typedef struct Node {
    char *line;
    struct Node *next;
} Node;

// Función para agregar una línea al inicio de la lista (para invertir el orden)
Node* add_line(Node *head, char *line) {
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    
    // Duplicar la línea para almacenarla
    new_node->line = malloc(strlen(line) + 1);
    if (new_node->line == NULL) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    strcpy(new_node->line, line);
    
    new_node->next = head;
    return new_node;
}

// Función para imprimir la lista y liberar memoria
void print_and_free_list(Node *head, FILE *output) {
    Node *current = head;
    while (current != NULL) {
        fprintf(output, "%s", current->line);
        Node *temp = current;
        current = current->next;
        free(temp->line);
        free(temp);
    }
}

// Función para verificar si dos archivos son el mismo
int same_file(const char *file1, const char *file2) {
    return strcmp(file1, file2) == 0;
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;
    FILE *output = stdout;
    Node *head = NULL;
    char *line = NULL;
    size_t len = 0;
    size_t read;
    
    // Verificar número de argumentos
    if (argc > 3) {
        fprintf(stderr, "usage: reverse <input> <output>\n");
        exit(1);
    }
    
    // Verificar si input y output son el mismo archivo
    if (argc == 3 && same_file(argv[1], argv[2])) {
        fprintf(stderr, "El archivo de entrada y salida deben diferir\n");
        exit(1);
    }
    
    // Abrir archivo de entrada si se especifica
    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[1]);
            exit(1);
        }
    }
    
    // Abrir archivo de salida si se especifica
    if (argc == 3) {
        output = fopen(argv[2], "w");
        if (output == NULL) {
            fprintf(stderr, "error: cannot open file '%s'\n", argv[2]);
            exit(1);
        }
    }
    
    // Leer líneas del archivo y almacenarlas en la lista enlazada
    while ((read = getline(&line, &len, input)) != -1) {
        head = add_line(head, line);
    }
    
    // Imprimir las líneas en orden inverso y liberar memoria
    print_and_free_list(head, output);
    
    // Liberar la línea temporal
    free(line);
    
    // Cerrar archivos si no son stdin/stdout
    if (input != stdin) {
        fclose(input);
    }
    if (output != stdout) {
        fclose(output);
    }
    
    return 0;
}