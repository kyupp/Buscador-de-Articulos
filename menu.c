#include "menu.h"

void limpiar_buffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

void pausar() {
  printf("\nPresione ENTER para continuar...");
  limpiar_buffer();
}

void mostrar_menu_principal() {
  printf("\n");
  printf(
      "╔══════════════════════════════════════════════════════════════════╗\n");
  printf(
      "║              SISTEMA DE GESTIÓN DE ARTÍCULOS                     ║\n");
  printf(
      "║           La Búsqueda de Sísifo - Corrupción en AL              ║\n");
  printf(
      "╚══════════════════════════════════════════════════════════════════╝\n");
  printf("\n");
  printf("  [1] Ordenar por Título de la Publicación\n");
  printf("  [2] Ordenar por Tamaño del Título (cantidad de palabras)\n");
  printf("  [3] Ordenar por Nombre del Archivo\n");
  printf("  [4] Ordenar por Relevancia (Año + Complejidad del título)\n");
  printf("  [5] Salir\n");
  printf("\n");
}

void mostrar_submenu_orden() {
  printf("\n");
  printf("  ┌─────────────────────────────┐\n");
  printf("  │   Orden de clasificación    │\n");
  printf("  └─────────────────────────────┘\n");
  printf("  [1] Ascendente (A→Z / menor→mayor)\n");
  printf("  [2] Descendente (Z→A / mayor→menor)\n");
  printf("\n");
}

int leer_entero_validado(const char *mensaje, int min, int max) {
  int valor;
  int leido;
  char buffer[256];

  while (1) {
    // Imprimir mensaje formateado
    snprintf(buffer, sizeof(buffer), mensaje, max);
    printf("%s", buffer);

    leido = scanf("%d", &valor);

    if (leido != 1) {
      printf(" Error: Debe ingresar un número.\n\n");
      limpiar_buffer();
      continue;
    }

    if (valor < min || valor > max) {
      printf(" Error: El valor debe estar entre %d y %d.\n\n", min, max);
      limpiar_buffer();
      continue;
    }

    limpiar_buffer();
    return valor;
  }
}
void mostrar_resultados(Articulo **resultados, int cantidad_total,
                        int cantidad_mostrar, const char *titulo_ordenamiento) {
  if (resultados == NULL || cantidad_total == 0) {
    printf("\n No hay resultados para mostrar.\n");
    return;
  }

  printf("\n");
  printf(
      "╔══════════════════════════════════════════════════════════════════╗\n");
  printf("║  RESULTADOS: %-51s ║\n", titulo_ordenamiento);
  printf(
      "╠══════════════════════════════════════════════════════════════════╣\n");
  printf(
      "║  Mostrando %d de %d artículos totales                            \n",
      cantidad_mostrar, cantidad_total);
  printf(
      "╚══════════════════════════════════════════════════════════════════╝\n");

  for (int i = 0; i < cantidad_mostrar && i < cantidad_total; i++) {
    if (resultados[i] != NULL) {
      mostrar_articulo(resultados[i], i + 1);
    }
  }

  if (cantidad_mostrar < cantidad_total) {
    printf("\n");
    printf("  Se omitieron %d artículos. Aumente la cantidad para ver más.\n",
           cantidad_total - cantidad_mostrar);
  }
}
