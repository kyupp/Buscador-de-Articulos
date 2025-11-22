#include "articulo.h"
#include "menu.h"
#include "ordenamientos.h"
#include <stdio.h>
#include <stdlib.h>

#define ARCHIVO_INDICE "archivo.txt"

int main() {
  Articulo *articulos = NULL;
  int cantidad_articulos = 0;

  // Cargar artículos
  printf("Cargando artículos desde '%s'...\n", ARCHIVO_INDICE);
  cantidad_articulos = leer_articulos(ARCHIVO_INDICE, &articulos);

  if (cantidad_articulos < 0) {
    fprintf(stderr, " Error al cargar los artículos.\n");
    return 1;
  }

  if (cantidad_articulos == 0) {
    printf(" No se encontraron artículos en el archivo.\n");
    return 0;
  }

  printf(" Se cargaron %d artículos correctamente.\n", cantidad_articulos);
  pausar();

  // Menú principal
  int opcion;
  int continuar = 1;

  while (continuar) {
    mostrar_menu_principal();
    opcion = leer_entero_validado("Seleccione una opción: ", 1, 5);

    if (opcion == 5) {
      continuar = 0;
      continue;
    }

    // Preguntar orden (ascendente/descendente)
    mostrar_submenu_orden();
    int tipo_orden = leer_entero_validado("Seleccione el orden: ", 1, 2);
    int ascendente = (tipo_orden == 1);

    // Preguntar cantidad de artículos a mostrar
    printf("\n");
    int cantidad_mostrar = leer_entero_validado(
        "¿Cuántos artículos desea ver? (1-%d): ", 1, cantidad_articulos);

    // Ejecutar ordenamiento
    Articulo **resultados = NULL;
    const char *nombre_ordenamiento = "";

    printf("\n Procesando ordenamiento...\n");

    switch (opcion) {
    case 1:
      resultados =
          ordenar_por_titulo(articulos, cantidad_articulos, ascendente);
      nombre_ordenamiento =
          ascendente ? "Por Título (A→Z)" : "Por Título (Z→A)";
      break;

    case 2:
      resultados =
          ordenar_por_tamanio_titulo(articulos, cantidad_articulos, ascendente);
      nombre_ordenamiento = ascendente ? "Por Tamaño de Título (Menor→Mayor)"
                                       : "Por Tamaño de Título (Mayor→Menor)";
      break;

    case 3:
      resultados =
          ordenar_por_nombre_archivo(articulos, cantidad_articulos, ascendente);
      nombre_ordenamiento = ascendente ? "Por Nombre de Archivo (A→Z)"
                                       : "Por Nombre de Archivo (Z→A)";
      break;

    case 4:
      resultados =
          ordenar_por_relevancia(articulos, cantidad_articulos, ascendente);
      nombre_ordenamiento = ascendente ? "Por Relevancia (Menor→Mayor)"
                                       : "Por Relevancia (Mayor→Menor)";
      break;
    }

    // Mostrar resultados
    if (resultados != NULL) {
      mostrar_resultados(resultados, cantidad_articulos, cantidad_mostrar,
                         nombre_ordenamiento);
      free(resultados);
    } else {
      printf("\n Error al realizar el ordenamiento.\n");
    }

    pausar();
  }

  // Despedida
  printf("\n");
  printf(
      "╔══════════════════════════════════════════════════════════════════╗\n");
  printf(
      "║                    Gracias por usar el sistema                   ║\n");
  printf(
      "║                  La Búsqueda de Sísifo - 2025                    ║\n");
  printf(
      "╚══════════════════════════════════════════════════════════════════╝\n");
  printf("\n");

  // Liberar memoria
  liberar_lista_articulos(articulos, cantidad_articulos);

  return 0;
}
