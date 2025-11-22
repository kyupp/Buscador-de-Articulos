#ifndef ORDENAMIENTOS_H
#define ORDENAMIENTOS_H

#include "articulo.h"
#include "heap_numerico.h"
#include "heap_string.h"

/**
 * Ordena artículos por título alfabéticamente
 * @param articulos: array de artículos
 * @param cantidad: número de artículos
 * @param ascendente: 1 para A-Z, 0 para Z-A
 * @return array ordenado de punteros a artículos
 */
Articulo **ordenar_por_titulo(Articulo *articulos, int cantidad,
                              int ascendente);

/**
 * Ordena artículos por cantidad de palabras en el título
 * @param articulos: array de artículos
 * @param cantidad: número de artículos
 * @param ascendente: 1 para menor a mayor, 0 para mayor a menor
 * @return array ordenado de punteros a artículos
 */
Articulo **ordenar_por_tamanio_titulo(Articulo *articulos, int cantidad,
                                      int ascendente);

/**
 * Ordena artículos por nombre de archivo
 * @param articulos: array de artículos
 * @param cantidad: número de artículos
 * @param ascendente: 1 para A-Z, 0 para Z-A
 * @return array ordenado de punteros a artículos
 */
Articulo **ordenar_por_nombre_archivo(Articulo *articulos, int cantidad,
                                      int ascendente);

/**
 * Ordena artículos por score personalizado:
 * Score = (Año - 2000) * 100 + palabras_en_titulo
 * Prioriza artículos recientes y con títulos más descriptivos
 * @param articulos: array de artículos
 * @param cantidad: número de artículos
 * @param ascendente: 1 para menor a mayor, 0 para mayor a menor
 * @return array ordenado de punteros a artículos
 */
Articulo **ordenar_por_relevancia(Articulo *articulos, int cantidad,
                                  int ascendente);

/**
 * Extrae el nombre del archivo de una ruta
 * @param ruta: ruta completa del archivo
 * @return puntero al nombre del archivo dentro de la ruta
 */
const char *extraer_nombre_archivo(const char *ruta);

/**
 * Calcula el score de relevancia de un artículo
 * @param articulo: artículo a evaluar
 * @return score calculado
 */
int calcular_score_relevancia(Articulo *articulo);

/**
 * Intercambia dos artículos (swap)
 * @param a: primer artículo
 * @param b: segundo artículo
 */
void intercambiar_articulos(Articulo *a, Articulo *b);

/**
 * Ordena artículos directamente en el array por título usando heapsort
 * @param articulos: array de artículos a ordenar
 * @param cantidad: número de artículos
 * @param ascendente: 1 para A-Z, 0 para Z-A
 */
void heapsort_por_titulo(Articulo *articulos, int cantidad, int ascendente);

/**
 * Ordena artículos directamente en el array por nombre de archivo usando
 * heapsort
 * @param articulos: array de artículos a ordenar
 * @param cantidad: número de artículos
 * @param ascendente: 1 para A-Z, 0 para Z-A
 */
void heapsort_por_nombre_archivo(Articulo *articulos, int cantidad,
                                 int ascendente);

#endif // ORDENAMIENTOS_H
