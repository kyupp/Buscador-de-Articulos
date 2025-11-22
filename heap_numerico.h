#ifndef HEAP_NUMERICO_H
#define HEAP_NUMERICO_H

#include "articulo.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Nodo del heap numérico
 */
typedef struct {
  int clave;       // Valor numérico para ordenar
  Articulo *datos; // Puntero al artículo
} NodoHeapNumerico;

/**
 * Estructura del heap numérico
 */
typedef struct {
  NodoHeapNumerico *array;
  int tamanio;
  int capacidad;
  int es_max_heap; // 1 para max-heap, 0 para min-heap
} HeapNumerico;

/**
 * Crea un nuevo heap numérico
 * @param capacidad_inicial: capacidad inicial del heap
 * @param es_max: 1 para max-heap, 0 para min-heap
 * @return puntero al heap creado
 */
HeapNumerico *crear_heap_numerico(int capacidad_inicial, int es_max);

/**
 * Inserta un elemento en el heap
 * @param heap: heap donde insertar
 * @param clave: valor numérico
 * @param articulo: puntero al artículo
 * @return 0 si éxito, -1 si error
 */
int insertar_heap_numerico(HeapNumerico *heap, int clave, Articulo *articulo);

/**
 * Extrae el elemento raíz del heap
 * @param heap: heap de donde extraer
 * @return puntero al artículo extraído, NULL si está vacío
 */
Articulo *extraer_heap_numerico(HeapNumerico *heap);

/**
 * Libera la memoria del heap
 * @param heap: heap a liberar
 */
void liberar_heap_numerico(HeapNumerico *heap);

/**
 * Verifica si el heap está vacío
 * @param heap: heap a verificar
 * @return 1 si está vacío, 0 si no
 */
int heap_numerico_vacio(HeapNumerico *heap);

#endif // HEAP_NUMERICO_H
