#include "heap_numerico.h"

/**
 * Intercambia dos nodos del heap
 */
static void intercambiar_nodos_numerico(NodoHeapNumerico* a, NodoHeapNumerico* b) {
    NodoHeapNumerico temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * Realiza heapify hacia arriba
 */
static void heapify_arriba_numerico(HeapNumerico* heap, int indice) {
    if (indice == 0) return;
    
    int padre = (indice - 1) / 2;
    
    if (heap->es_max_heap) {
        // Max-heap: el padre debe ser mayor
        if (heap->array[indice].clave > heap->array[padre].clave) {
            intercambiar_nodos_numerico(&heap->array[indice], &heap->array[padre]);
            heapify_arriba_numerico(heap, padre);
        }
    } else {
        // Min-heap: el padre debe ser menor
        if (heap->array[indice].clave < heap->array[padre].clave) {
            intercambiar_nodos_numerico(&heap->array[indice], &heap->array[padre]);
            heapify_arriba_numerico(heap, padre);
        }
    }
}

/**
 * Realiza heapify hacia abajo
 */
static void heapify_abajo_numerico(HeapNumerico* heap, int indice) {
    int izquierdo = 2 * indice + 1;
    int derecho = 2 * indice + 2;
    int objetivo = indice;
    
    if (heap->es_max_heap) {
        // Max-heap: buscar el mayor
        if (izquierdo < heap->tamanio && 
            heap->array[izquierdo].clave > heap->array[objetivo].clave) {
            objetivo = izquierdo;
        }
        if (derecho < heap->tamanio && 
            heap->array[derecho].clave > heap->array[objetivo].clave) {
            objetivo = derecho;
        }
    } else {
        // Min-heap: buscar el menor
        if (izquierdo < heap->tamanio && 
            heap->array[izquierdo].clave < heap->array[objetivo].clave) {
            objetivo = izquierdo;
        }
        if (derecho < heap->tamanio && 
            heap->array[derecho].clave < heap->array[objetivo].clave) {
            objetivo = derecho;
        }
    }
    
    if (objetivo != indice) {
        intercambiar_nodos_numerico(&heap->array[indice], &heap->array[objetivo]);
        heapify_abajo_numerico(heap, objetivo);
    }
}

HeapNumerico* crear_heap_numerico(int capacidad_inicial, int es_max) {
    HeapNumerico* heap = (HeapNumerico*) malloc(sizeof(HeapNumerico));
    if (heap == NULL) {
        perror("Error al crear heap numérico");
        return NULL;
    }
    
    heap->array = (NodoHeapNumerico*) malloc(capacidad_inicial * sizeof(NodoHeapNumerico));
    if (heap->array == NULL) {
        perror("Error al crear array del heap");
        free(heap);
        return NULL;
    }
    
    heap->tamanio = 0;
    heap->capacidad = capacidad_inicial;
    heap->es_max_heap = es_max;
    
    return heap;
}

int insertar_heap_numerico(HeapNumerico* heap, int clave, Articulo* articulo) {
    if (heap == NULL || articulo == NULL) {
        return -1;
    }
    
    // Expandir si es necesario
    if (heap->tamanio >= heap->capacidad) {
        int nueva_capacidad = heap->capacidad * 2;
        NodoHeapNumerico* nuevo_array = (NodoHeapNumerico*) realloc(heap->array, 
                                                nueva_capacidad * sizeof(NodoHeapNumerico));
        if (nuevo_array == NULL) {
            perror("Error al expandir el heap");
            return -1;
        }
        heap->array = nuevo_array;
        heap->capacidad = nueva_capacidad;
    }
    
    // Insertar al final
    heap->array[heap->tamanio].clave = clave;
    heap->array[heap->tamanio].datos = articulo;
    
    // Hacer heapify hacia arriba
    heapify_arriba_numerico(heap, heap->tamanio);
    heap->tamanio++;
    
    return 0;
}

Articulo* extraer_heap_numerico(HeapNumerico* heap) {
    if (heap == NULL || heap->tamanio == 0) {
        return NULL;
    }
    
    // Guardar el elemento raíz
    Articulo* resultado = heap->array[0].datos;
    
    // Mover el último elemento a la raíz
    heap->tamanio--;
    if (heap->tamanio > 0) {
        heap->array[0] = heap->array[heap->tamanio];
        heapify_abajo_numerico(heap, 0);
    }
    
    return resultado;
}

void liberar_heap_numerico(HeapNumerico* heap) {
    if (heap == NULL) return;
    
    free(heap->array);
    free(heap);
}

int heap_numerico_vacio(HeapNumerico* heap) {
    return (heap == NULL || heap->tamanio == 0);
}