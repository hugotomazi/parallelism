/*
    UNIVALI - Universidade do Vale do Itajaí
    Trabalho desenvolvido para a disciplina de Sistemas Operacionais
    Autor: Hugo Tomazi Busnardo

    Comando para build:
    g++ -fopenmp main.cpp -o build/openmp
*/
#include <omp.h>
#include <random>
#include <iostream>
#include <time.h>

using namespace std;

#define LINHAS 100
#define COLUNAS 500


int m1[LINHAS][COLUNAS];
int m2[COLUNAS][LINHAS];
int resultado[LINHAS][COLUNAS];

void initMatrix() {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0,LINHAS*COLUNAS);
    for(int i = 0; i < LINHAS; ++i) {
        for(int j = 0; j < COLUNAS; ++j) {
            m1[i][j] = dist6(rng);
            m2[j][i] = dist6(rng);
        }
    }
}

int main(int argc, char *argv[]) {
    double inicio, fim;
    initMatrix();
    omp_set_num_threads(2);
    cout << omp_get_num_threads();

    inicio = (double) clock() / CLOCKS_PER_SEC;
    #pragma omp parallel for
    for(int i = 0; i < LINHAS; ++i) {
        for(int j = 0; j < COLUNAS; ++j) {
            resultado[i][j] = m1[i][j] * m2[j][i];
        }
    }
    fim = (double) clock() / CLOCKS_PER_SEC;

    cout << "Tempo de execução: " << (fim - inicio) << endl;
    return 0;
}