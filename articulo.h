#ifndef ARTICULO_H
#define ARTICULO_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITADOR "|"
#define MAX_LINEA 4096

/**
 * Estructura que representa un artículo científico
 */
typedef struct {
  char nombre[256];    // Nombre del autor
  char apellido[256];  // Apellido del autor
  char titulo[512];    // Título del artículo
  char ruta[512];      // Ruta del archivo PDF
  char fecha[64];      // Año de publicación
  char abstract[1024]; // Resumen del artículo
  int palabras_titulo; // Cantidad de palabras en el título
  int ano;             // Año como entero
} Articulo;

/**
 * Cuenta las palabras en un texto
 * @param texto: cadena a analizar
 * @return cantidad de palabras
 */
int contar_palabras(const char *texto);

/**
 * Lee los artículos desde un archivo delimitado por |
 * @param nombre_archivo: ruta del archivo a leer
 * @param lista_articulos: puntero donde se almacenará la lista
 * @return cantidad de artículos leídos, -1 si hay error
 */
int leer_articulos(const char *nombre_archivo, Articulo **lista_articulos);

/**
 * Libera la memoria de un array de artículos
 * @param lista: array de artículos
 * @param cantidad: número de artículos
 */
void liberar_lista_articulos(Articulo *lista, int cantidad);

/**
 * Extrae el nombre del archivo de una ruta completa
 * @param ruta: ruta completa del archivo
 * @param salida: buffer donde se almacenará el nombre
 */
void extraer_nombre_archivo_a_buffer(const char *ruta, char *salida);

/**
 * Muestra la información de un artículo
 * @param art: artículo a mostrar
 * @param num: número del artículo en la lista
 */
void mostrar_articulo(Articulo *art, int num);

#endif // ARTICULO_H
