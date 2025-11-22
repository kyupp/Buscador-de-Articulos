#ifndef HEAP_STRING_H
#define HEAP_STRING_H

#include "articulo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Nodo del heap de strings
 */
typedef struct {
  char *clave;     // String para ordenar
  Articulo *datos; // Puntero al artículo
} NodoHeapString;

/**
 * Estructura del heap de strings
 */
typedef struct {
  NodoHeapString *array;
  int tamanio;
  int capacidad;
  int orden_ascendente; // 1 para ascendente (A-Z), 0 para descendente (Z-A)
} HeapString;

/**
 * Crea un nuevo heap de strings
 * @param capacidad_inicial: capacidad inicial del heap
 * @param ascendente: 1 para orden A-Z, 0 para Z-A
 * @return puntero al heap creado
 */
HeapString *crear_heap_string(int capacidad_inicial, int ascendente);

/**
 * Inserta un elemento en el heap
 * @param heap: heap donde insertar
 * @param clave: string para ordenar
 * @param articulo: puntero al artículo
 * @return 0 si éxito, -1 si error
 */
int insertar_heap_string(HeapString *heap, const char *clave,
                         Articulo *articulo);

/**
 * Extrae el elemento raíz del heap
 * @param heap: heap de donde extraer
 * @return puntero al artículo extraído, NULL si está vacío
 */
Articulo *extraer_heap_string(HeapString *heap);

/**
 * Libera la memoria del heap
 * @param heap: heap a liberar
 */
void liberar_heap_string(HeapString *heap);

/**
 * Verifica si el heap está vacío
 * @param heap: heap a verificar
 * @return 1 si está vacío, 0 si no
 */
int heap_string_vacio(HeapString *heap);

#endif // HEAP_STRING_H
