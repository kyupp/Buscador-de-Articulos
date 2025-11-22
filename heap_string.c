#include "heap_string.h"

/**
 * Intercambia dos nodos del heap
 */
static void intercambiar_nodos_string(NodoHeapString *a, NodoHeapString *b) {
  NodoHeapString temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * Compara dos strings según el orden del heap
 * Retorna: < 0 si a debe estar antes que b
 *          > 0 si b debe estar antes que a
 *            0 si son iguales
 */
static int comparar_strings(HeapString *heap, const char *a, const char *b) {
  if (heap->orden_ascendente) {
    return strcmp(a, b); // A-Z
  } else {
    return strcmp(b, a); // Z-A
  }
}

/**
 * Realiza heapify hacia arriba
 */
static void heapify_arriba_string(HeapString *heap, int indice) {
  if (indice == 0)
    return;

  int padre = (indice - 1) / 2;

  // Min-heap para strings (el menor lexicográficamente sube)
  if (comparar_strings(heap, heap->array[indice].clave,
                       heap->array[padre].clave) < 0) {
    intercambiar_nodos_string(&heap->array[indice], &heap->array[padre]);
    heapify_arriba_string(heap, padre);
  }
}

/**
 * Realiza heapify hacia abajo
 */
static void heapify_abajo_string(HeapString *heap, int indice) {
  int izquierdo = 2 * indice + 1;
  int derecho = 2 * indice + 2;
  int menor = indice;

  if (izquierdo < heap->tamanio &&
      comparar_strings(heap, heap->array[izquierdo].clave,
                       heap->array[menor].clave) < 0) {
    menor = izquierdo;
  }

  if (derecho < heap->tamanio &&
      comparar_strings(heap, heap->array[derecho].clave,
                       heap->array[menor].clave) < 0) {
    menor = derecho;
  }

  if (menor != indice) {
    intercambiar_nodos_string(&heap->array[indice], &heap->array[menor]);
    heapify_abajo_string(heap, menor);
  }
}

HeapString *crear_heap_string(int capacidad_inicial, int ascendente) {
  HeapString *heap = (HeapString *)malloc(sizeof(HeapString));
  if (heap == NULL) {
    perror("Error al crear heap de strings");
    return NULL;
  }

  heap->array =
      (NodoHeapString *)malloc(capacidad_inicial * sizeof(NodoHeapString));
  if (heap->array == NULL) {
    perror("Error al crear array del heap");
    free(heap);
    return NULL;
  }

  heap->tamanio = 0;
  heap->capacidad = capacidad_inicial;
  heap->orden_ascendente = ascendente;

  return heap;
}

int insertar_heap_string(HeapString *heap, const char *clave,
                         Articulo *articulo) {
  if (heap == NULL || clave == NULL || articulo == NULL) {
    return -1;
  }

  // Expandir si es necesario
  if (heap->tamanio >= heap->capacidad) {
    int nueva_capacidad = heap->capacidad * 2;
    NodoHeapString *nuevo_array = (NodoHeapString *)realloc(
        heap->array, nueva_capacidad * sizeof(NodoHeapString));
    if (nuevo_array == NULL) {
      perror("Error al expandir el heap");
      return -1;
    }
    heap->array = nuevo_array;
    heap->capacidad = nueva_capacidad;
  }

  // Insertar al final
  heap->array[heap->tamanio].clave = strdup(clave);
  if (heap->array[heap->tamanio].clave == NULL) {
    perror("Error al duplicar clave");
    return -1;
  }
  heap->array[heap->tamanio].datos = articulo;

  // Hacer heapify hacia arriba
  heapify_arriba_string(heap, heap->tamanio);
  heap->tamanio++;

  return 0;
}

Articulo *extraer_heap_string(HeapString *heap) {
  if (heap == NULL || heap->tamanio == 0) {
    return NULL;
  }

  // Guardar el elemento raíz
  Articulo *resultado = heap->array[0].datos;
  free(heap->array[0].clave);

  // Mover el último elemento a la raíz
  heap->tamanio--;
  if (heap->tamanio > 0) {
    heap->array[0] = heap->array[heap->tamanio];
    heapify_abajo_string(heap, 0);
  }

  return resultado;
}

void liberar_heap_string(HeapString *heap) {
  if (heap == NULL)
    return;

  // Liberar las claves restantes
  for (int i = 0; i < heap->tamanio; i++) {
    free(heap->array[i].clave);
  }

  free(heap->array);
  free(heap);
}

int heap_string_vacio(HeapString *heap) {
  return (heap == NULL || heap->tamanio == 0);
}
