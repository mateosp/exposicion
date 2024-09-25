#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_OBJECTS 10 // Número total de objetos simulados

// Estructura de un objeto
typedef struct Object {
    bool marked;           // Indicador de si el objeto está marcado (alcanzable)
    struct Object* ref1;   // Referencia a otro objeto
    struct Object* ref2;   // Otra referencia
} Object;

// Un simple heap simulado
Object* heap[NUM_OBJECTS];

// Función para crear un nuevo objeto
Object* create_object() {
    Object* obj = (Object*)malloc(sizeof(Object));
    obj->marked = false;  // Inicialmente no está marcado
    obj->ref1 = NULL;     // Sin referencias aún
    obj->ref2 = NULL;
    return obj;
}

// Fase de marcación (Mark): Marcar los objetos alcanzables
void mark(Object* obj) {
    if (obj == NULL || obj->marked) return; // Si es NULL o ya está marcado, no hacemos nada

    obj->marked = true;  // Marcamos el objeto
    printf("Marcando objeto %p\n", obj);
    
    // Recursivamente marcamos los objetos referenciados
    mark(obj->ref1);
    mark(obj->ref2);
}

// Fase de barrido (Sweep): Barrer y eliminar los objetos no marcados
void sweep() {
    for (int i = 0; i < NUM_OBJECTS; i++) {
        if (heap[i] != NULL && !heap[i]->marked) {
            // Si el objeto no está marcado, lo eliminamos
            printf("Barriendo objeto %p\n", heap[i]);
            free(heap[i]);
            heap[i] = NULL;
        } else if (heap[i] != NULL) {
            // Si está marcado, lo desmarcamos para la próxima ejecución
            heap[i]->marked = false;
        }
    }
}

// Función para simular el recolector de basura
void garbage_collect(Object* root) {
    // 1. Fase de marcado
    printf("Fase de marcado\n");
    mark(root);
    
    // 2. Fase de barrido
    printf("Fase de barrido\n");
    sweep();
}

int main() {
    // Inicializamos el heap con objetos
    for (int i = 0; i < NUM_OBJECTS; i++) {
        heap[i] = create_object();
    }

    // Creamos referencias entre los objetos para simular un grafo de objetos
    heap[0]->ref1 = heap[1];  // El objeto 0 referencia al objeto 1
    heap[1]->ref1 = heap[2];  // El objeto 1 referencia al objeto 2
    heap[2]->ref1 = heap[3];  // El objeto 2 referencia al objeto 3
    
    // Simulamos que el objeto root es heap[0] (el único accesible desde el "mundo real")
    Object* root = heap[0];
    
    // Ejecutamos la recolección de basura
    garbage_collect(root);
    
    return 0;
}
