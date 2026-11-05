#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int fila;
    int col;
    double valor;
} ElementoEsparso;

void generar_matriz_txt(const char* nombre_archivo, int filas, int columnas) {
    FILE *archivo = fopen(nombre_archivo, "w");
    if (!archivo) return;

    fprintf(archivo, "%d %d\n", filas, columnas);
    
    int nro_elementos = (int)((filas * columnas) * 0.05);

    for (int k = 0; k < nro_elementos; k++) {
        int i = rand() % filas;
        int j = rand() % columnas;
        double valor = (rand() % 100) + 1.5;
        fprintf(archivo, "%d %d %.2f\n", i, j, valor);
    }
    fclose(archivo);
    printf("Paso 1: Archivo %s generado (%d elementos).\n", nombre_archivo, nro_elementos);
}

void convertir_txt_a_binario(const char* txt_filename, const char* bin_filename) {
    FILE *f_txt = fopen(txt_filename, "r");
    FILE *f_bin = fopen(bin_filename, "wb");
    if (!f_txt || !f_bin) return;

    int filas, columnas;
    fscanf(f_txt, "%d %d", &filas, &columnas);

    ElementoEsparso celda;
    while (fscanf(f_txt, "%d %d %lf", &celda.fila, &celda.col, &celda.valor) == 3) {
        fwrite(&celda, sizeof(ElementoEsparso), 1, f_bin);
    }

    fclose(f_txt);
    fclose(f_bin);
    printf("Paso 2: Convertido %s a formato binario.\n", txt_filename);
}

int main() {
    srand(time(NULL));

    int M = 1000; 
    int N = 1000; 
    int P = 1000; 

    printf("Iniciando procesamiento de matrices esparsas...\n\n");

    generar_matriz_txt("matriz_a.txt", M, N);
    generar_matriz_txt("matriz_b.txt", N, P);

    convertir_txt_a_binario("matriz_a.txt", "matriz_a.bin");
    convertir_txt_a_binario("matriz_b.txt", "matriz_b.bin");

    printf("\nProceso finalizado con exito.\n");
    return 0;
}