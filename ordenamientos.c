#include "ordenamientos.h"

const char *extraer_nombre_archivo(const char *ruta) {
  if (ruta == NULL)
    return "";

  const char *ultimo_slash = strrchr(ruta, '/');
  if (ultimo_slash != NULL) {
    return ultimo_slash + 1;
  }
  return ruta;
}

/**
 * Intercambia dos artículos
 */
void intercambiar_articulos(Articulo *a, Articulo *b) {
  Articulo temp = *a;
  *a = *b;
  *b = temp;
}

int calcular_score_relevancia(Articulo *articulo) {
  if (articulo == NULL || articulo->fecha[0] == '\0') {
    return 0;
  }

  int anio = atoi(articulo->fecha);
  if (anio < 1900 || anio > 2100) {
    anio = 2000; // Valor por defecto
  }

  // Score = (Año - 2000) * 100 + palabras en título
  // Esto prioriza artículos recientes y con títulos descriptivos
  int score = (anio - 2000) * 100 + articulo->palabras_titulo;

  return score;
}

Articulo **ordenar_por_titulo(Articulo *articulos, int cantidad,
                              int ascendente) {
  if (articulos == NULL || cantidad <= 0) {
    return NULL;
  }

  // Crear heap de strings
  HeapString *heap = crear_heap_string(cantidad, ascendente);
  if (heap == NULL) {
    return NULL;
  }

  // Insertar todos los artículos en el heap
  for (int i = 0; i < cantidad; i++) {
    if (insertar_heap_string(heap, articulos[i].titulo, &articulos[i]) != 0) {
      liberar_heap_string(heap);
      return NULL;
    }
  }

  // Extraer en orden
  Articulo **resultado = (Articulo **)malloc(cantidad * sizeof(Articulo *));
  if (resultado == NULL) {
    liberar_heap_string(heap);
    return NULL;
  }

  for (int i = 0; i < cantidad; i++) {
    resultado[i] = extraer_heap_string(heap);
  }

  liberar_heap_string(heap);
  return resultado;
}

Articulo **ordenar_por_tamanio_titulo(Articulo *articulos, int cantidad,
                                      int ascendente) {
  if (articulos == NULL || cantidad <= 0) {
    return NULL;
  }

  // Crear heap numérico
  // Para ascendente: min-heap (0), para descendente: max-heap (1)
  HeapNumerico *heap = crear_heap_numerico(cantidad, !ascendente);
  if (heap == NULL) {
    return NULL;
  }

  // Insertar todos los artículos en el heap
  for (int i = 0; i < cantidad; i++) {
    int clave = articulos[i].palabras_titulo;
    if (insertar_heap_numerico(heap, clave, &articulos[i]) != 0) {
      liberar_heap_numerico(heap);
      return NULL;
    }
  }

  // Extraer en orden
  Articulo **resultado = (Articulo **)malloc(cantidad * sizeof(Articulo *));
  if (resultado == NULL) {
    liberar_heap_numerico(heap);
    return NULL;
  }

  for (int i = 0; i < cantidad; i++) {
    resultado[i] = extraer_heap_numerico(heap);
  }

  liberar_heap_numerico(heap);
  return resultado;
}

/**
 * Heapify para ordenamiento por título
 */
static void heapify_titulo(Articulo *arr, int n, int i, int ascendente) {
  int objetivo = i;
  int izq = 2 * i + 1;
  int der = 2 * i + 2;

  if (ascendente) {
    // Max-heap para orden ascendente (A→Z)
    if (izq < n && strcmp(arr[izq].titulo, arr[objetivo].titulo) > 0)
      objetivo = izq;
    if (der < n && strcmp(arr[der].titulo, arr[objetivo].titulo) > 0)
      objetivo = der;
  } else {
    // Min-heap para orden descendente (Z→A)
    if (izq < n && strcmp(arr[izq].titulo, arr[objetivo].titulo) < 0)
      objetivo = izq;
    if (der < n && strcmp(arr[der].titulo, arr[objetivo].titulo) < 0)
      objetivo = der;
  }

  if (objetivo != i) {
    intercambiar_articulos(&arr[i], &arr[objetivo]);
    heapify_titulo(arr, n, objetivo, ascendente);
  }
}

void heapsort_por_titulo(Articulo *articulos, int cantidad, int ascendente) {
  if (articulos == NULL || cantidad <= 0)
    return;

  // Construir heap
  for (int i = cantidad / 2 - 1; i >= 0; i--) {
    heapify_titulo(articulos, cantidad, i, ascendente);
  }

  // Extraer elementos del heap
  for (int i = cantidad - 1; i > 0; i--) {
    intercambiar_articulos(&articulos[0], &articulos[i]);
    heapify_titulo(articulos, i, 0, ascendente);
  }
}

/**
 * Heapify para ordenamiento por nombre de archivo
 */
static void heapify_nombre_archivo(Articulo *arr, int n, int i,
                                   int ascendente) {
  int objetivo = i;
  int izq = 2 * i + 1;
  int der = 2 * i + 2;

  char nombre_objetivo[256], nombre_cmp[256];
  extraer_nombre_archivo_a_buffer(arr[objetivo].ruta, nombre_objetivo);

  if (ascendente) {
    // Max-heap para orden ascendente
    if (izq < n) {
      extraer_nombre_archivo_a_buffer(arr[izq].ruta, nombre_cmp);
      if (strcmp(nombre_cmp, nombre_objetivo) > 0)
        objetivo = izq;
    }
    if (der < n) {
      extraer_nombre_archivo_a_buffer(arr[objetivo].ruta, nombre_objetivo);
      extraer_nombre_archivo_a_buffer(arr[der].ruta, nombre_cmp);
      if (strcmp(nombre_cmp, nombre_objetivo) > 0)
        objetivo = der;
    }
  } else {
    // Min-heap para orden descendente
    if (izq < n) {
      extraer_nombre_archivo_a_buffer(arr[izq].ruta, nombre_cmp);
      if (strcmp(nombre_cmp, nombre_objetivo) < 0)
        objetivo = izq;
    }
    if (der < n) {
      extraer_nombre_archivo_a_buffer(arr[objetivo].ruta, nombre_objetivo);
      extraer_nombre_archivo_a_buffer(arr[der].ruta, nombre_cmp);
      if (strcmp(nombre_cmp, nombre_objetivo) < 0)
        objetivo = der;
    }
  }

  if (objetivo != i) {
    intercambiar_articulos(&arr[i], &arr[objetivo]);
    heapify_nombre_archivo(arr, n, objetivo, ascendente);
  }
}

void heapsort_por_nombre_archivo(Articulo *articulos, int cantidad,
                                 int ascendente) {
  if (articulos == NULL || cantidad <= 0)
    return;

  // Construir heap
  for (int i = cantidad / 2 - 1; i >= 0; i--) {
    heapify_nombre_archivo(articulos, cantidad, i, ascendente);
  }

  // Extraer elementos del heap
  for (int i = cantidad - 1; i > 0; i--) {
    intercambiar_articulos(&articulos[0], &articulos[i]);
    heapify_nombre_archivo(articulos, i, 0, ascendente);
  }
}

Articulo **ordenar_por_nombre_archivo(Articulo *articulos, int cantidad,
                                      int ascendente) {
  if (articulos == NULL || cantidad <= 0) {
    return NULL;
  }

  // Crear heap de strings
  HeapString *heap = crear_heap_string(cantidad, ascendente);
  if (heap == NULL) {
    return NULL;
  }

  // Insertar todos los artículos en el heap usando el nombre del archivo
  for (int i = 0; i < cantidad; i++) {
    const char *nombre = extraer_nombre_archivo(articulos[i].ruta);
    if (insertar_heap_string(heap, nombre, &articulos[i]) != 0) {
      liberar_heap_string(heap);
      return NULL;
    }
  }

  // Extraer en orden
  Articulo **resultado = (Articulo **)malloc(cantidad * sizeof(Articulo *));
  if (resultado == NULL) {
    liberar_heap_string(heap);
    return NULL;
  }

  for (int i = 0; i < cantidad; i++) {
    resultado[i] = extraer_heap_string(heap);
  }

  liberar_heap_string(heap);
  return resultado;
}

Articulo **ordenar_por_relevancia(Articulo *articulos, int cantidad,
                                  int ascendente) {
  if (articulos == NULL || cantidad <= 0) {
    return NULL;
  }

  // Crear heap numérico
  // Para ascendente: min-heap (0), para descendente: max-heap (1)
  HeapNumerico *heap = crear_heap_numerico(cantidad, !ascendente);
  if (heap == NULL) {
    return NULL;
  }

  // Insertar todos los artículos con su score
  for (int i = 0; i < cantidad; i++) {
    int score = calcular_score_relevancia(&articulos[i]);
    if (insertar_heap_numerico(heap, score, &articulos[i]) != 0) {
      liberar_heap_numerico(heap);
      return NULL;
    }
  }

  // Extraer en orden
  Articulo **resultado = (Articulo **)malloc(cantidad * sizeof(Articulo *));
  if (resultado == NULL) {
    liberar_heap_numerico(heap);
    return NULL;
  }

  for (int i = 0; i < cantidad; i++) {
    resultado[i] = extraer_heap_numerico(heap);
  }

  liberar_heap_numerico(heap);
  return resultado;
}
