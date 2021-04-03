/*
    UNIVALI - Universidade do Vale do Itajaí
    Trabalho desenvolvido para a disciplina de Sistemas Operacionais

    Autor: Hugo Tomazi Busnardo


*/
#include <omp.h>
#include <stdlib.h>
#include <random>
#include <string>
#include <iostream>
#include <time.h>

using namespace std;

#define LINHAS 3
#define COLUNAS 2


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
    initMatrix();

    clock_t inicio = clock();
    #pragma omp parallel for
    for(int i = 0; i < LINHAS; ++i) {
        for(int j = 0; j < COLUNAS; ++j) {
            resultado[i][j] = m1[i][j] * m2[j][i];
        }
    }
    clock_t fim = clock();

    cout << "Tempo de execução: " << (fim - inicio) << endl;
    return 0;
}