#include <stdio.h>
#include <stdlib.h>

// Definimos una estructura para el objeto con un contador de referencias
typedef struct {
    int value;      // Valor del objeto
    int ref_count;  // Contador de referencias
} RefObject;

// Función para crear un nuevo objeto
RefObject* create_object(int value) {
    RefObject* obj = (RefObject*)malloc(sizeof(RefObject)); // Reservamos memoria para el objeto
    obj->value = value;    // Asignamos el valor
    obj->ref_count = 1;    // Inicializamos el contador de referencias a 1
    return obj;            // Retornamos el nuevo objeto
}

// Incrementa el contador de referencias
void add_reference(RefObject* obj) {
    obj->ref_count++;      // Aumentamos el contador
}

// Decrementa el contador de referencias y libera si llega a 0
void remove_reference(RefObject* obj) {
    obj->ref_count--;      // Disminuimos el contador
    if (obj->ref_count == 0) {
        free(obj);         // Liberamos la memoria si no hay más referencias
        printf("Objeto liberado\n");
    }
}

int main() {
    RefObject* obj1 = create_object(42);  // Creamos un objeto con valor 42
    printf("Objeto creado con valor: %d, referencias: %d\n", obj1->value, obj1->ref_count);
    
    add_reference(obj1);  // Añadimos una referencia
    printf("Referencias después de agregar: %d\n", obj1->ref_count);
    
    remove_reference(obj1);  // Quitamos una referencia
    printf("Referencias después de quitar: %d\n", obj1->ref_count);
    
    remove_reference(obj1);  // Eliminamos la última referencia, lo que libera el objeto
    return 0;
}
