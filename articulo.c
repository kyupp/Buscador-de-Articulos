#define _GNU_SOURCE
#include "articulo.h"

int contar_palabras(const char *texto) {
  if (texto == NULL || strlen(texto) == 0) {
    return 0;
  }

  int contador = 0;
  int en_palabra = 0;

  for (int i = 0; texto[i] != '\0'; i++) {
    if (isspace(texto[i]) || texto[i] == '-') {
      en_palabra = 0;
    } else if (!en_palabra) {
      en_palabra = 1;
      contador++;
    }
  }
  return contador;
}

int leer_articulos(const char *nombre_archivo, Articulo **lista_articulos) {
  FILE *archivo = fopen(nombre_archivo, "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return -1;
  }

  char linea[MAX_LINEA];
  int contador = 0;
  int capacidad = 10;

  Articulo *lista_articulos_temp =
      (Articulo *)malloc(capacidad * sizeof(Articulo));
  if (lista_articulos_temp == NULL) {
    perror("Error al asignar memoria inicial");
    fclose(archivo);
    return -1;
  }

  while (fgets(linea, MAX_LINEA, archivo) != NULL) {
    // Limpiar el salto de línea
    linea[strcspn(linea, "\n")] = 0;
    linea[strcspn(linea, "\r")] = 0;

    if (strlen(linea) == 0) {
      continue;
    }

    // Expandir si es necesario
    if (contador >= capacidad) {
      capacidad *= 2;
      Articulo *nuevo_espacio = (Articulo *)realloc(
          lista_articulos_temp, capacidad * sizeof(Articulo));
      if (nuevo_espacio == NULL) {
        perror("Error al expandir memoria");
        fclose(archivo);
        free(lista_articulos_temp);
        return -1;
      }
      lista_articulos_temp = nuevo_espacio;
    }

    // Inicializar el artículo actual
    Articulo *art = &lista_articulos_temp[contador];
    art->nombre[0] = '\0';
    art->apellido[0] = '\0';
    art->titulo[0] = '\0';
    art->ruta[0] = '\0';
    art->fecha[0] = '\0';
    art->abstract[0] = '\0';
    art->palabras_titulo = 0;
    art->ano = 0;

    // Parsear la línea
    char linea_copia[MAX_LINEA];
    strncpy(linea_copia, linea, MAX_LINEA - 1);
    linea_copia[MAX_LINEA - 1] = '\0';

    char *token = strtok(linea_copia, DELIMITADOR);
    int campo = 0;

    while (token != NULL && campo < 6) {
      // Eliminar espacios al inicio y final
      while (isspace(*token))
        token++;
      char *fin = token + strlen(token) - 1;
      while (fin > token && isspace(*fin)) {
        *fin = '\0';
        fin--;
      }

      if (strlen(token) > 0) {
        switch (campo) {
        case 0: // Nombre
          strncpy(art->nombre, token, sizeof(art->nombre) - 1);
          art->nombre[sizeof(art->nombre) - 1] = '\0';
          break;
        case 1: // Apellido
          strncpy(art->apellido, token, sizeof(art->apellido) - 1);
          art->apellido[sizeof(art->apellido) - 1] = '\0';
          break;
        case 2: // Título
          strncpy(art->titulo, token, sizeof(art->titulo) - 1);
          art->titulo[sizeof(art->titulo) - 1] = '\0';
          art->palabras_titulo = contar_palabras(token);
          break;
        case 3: // Ruta
          strncpy(art->ruta, token, sizeof(art->ruta) - 1);
          art->ruta[sizeof(art->ruta) - 1] = '\0';
          break;
        case 4: // Fecha
          strncpy(art->fecha, token, sizeof(art->fecha) - 1);
          art->fecha[sizeof(art->fecha) - 1] = '\0';
          art->ano = atoi(token);
          break;
        case 5: // Abstract
          strncpy(art->abstract, token, sizeof(art->abstract) - 1);
          art->abstract[sizeof(art->abstract) - 1] = '\0';
          break;
        }
      }
      campo++;
      token = strtok(NULL, DELIMITADOR);
    }

    contador++;
  }

  fclose(archivo);
  *lista_articulos = lista_articulos_temp;
  return contador;
}

void liberar_lista_articulos(Articulo *lista, int cantidad) {
  if (lista == NULL)
    return;
  (void)cantidad;
  free(lista);
}

void mostrar_articulo(Articulo *art, int num) {
  printf("\n");
  printf(
      "═══════════════════════════════════════════════════════════════════\n");
  printf("  ARTÍCULO #%d\n", num);
  printf(
      "═══════════════════════════════════════════════════════════════════\n");
  printf("Título:   %s\n", art->titulo);
  printf("Autor:    %s %s\n", art->nombre, art->apellido);
  printf("Año:      %s\n", art->fecha);
  printf("Resumen:  %s\n", art->abstract);
  printf("Ruta:     %s\n", art->ruta);
  printf("Palabras: %d\n", art->palabras_titulo);
  printf(
      "═══════════════════════════════════════════════════════════════════\n");
}

void extraer_nombre_archivo_a_buffer(const char *ruta, char *salida) {
  if (ruta == NULL || salida == NULL) {
    if (salida != NULL)
      salida[0] = '\0';
    return;
  }

  const char *ultimo_slash = strrchr(ruta, '/');
  if (ultimo_slash != NULL) {
    strcpy(salida, ultimo_slash + 1);
  } else {
    strcpy(salida, ruta);
  }
}
