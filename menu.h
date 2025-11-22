#ifndef MENU_H
#define MENU_H

#include "articulo.h"
#include "ordenamientos.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Muestra el menú principal
 */
void mostrar_menu_principal();

/**
 * Muestra el submenú de ordenamiento
 */
void mostrar_submenu_orden();

/**
 * Lee un número entero con validación
 * @param mensaje: mensaje a mostrar
 * @param min: valor mínimo aceptable
 * @param max: valor máximo aceptable
 * @return número leído y validado
 */
int leer_entero_validado(const char *mensaje, int min, int max);

/**
 * Limpia el buffer de entrada
 */
void limpiar_buffer();

/**
 * Muestra los resultados de un ordenamiento
 * @param resultados: array de punteros a artículos ordenados
 * @param cantidad_total: cantidad total de artículos
 * @param cantidad_mostrar: cantidad de artículos a mostrar
 * @param titulo_ordenamiento: nombre del ordenamiento aplicado
 */
void mostrar_resultados(Articulo **resultados, int cantidad_total,
                        int cantidad_mostrar, const char *titulo_ordenamiento);

/**
 * Pausa la ejecución hasta que el usuario presione Enter
 */
void pausar();

#endif // MENU_H
