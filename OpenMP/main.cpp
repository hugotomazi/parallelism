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

using namespace std;

#define LINHAS 5
#define COLUNAS 3


int m1[LINHAS][COLUNAS];
int m2[COLUNAS][LINHAS];
string resultado[LINHAS][COLUNAS];

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

    #pragma omp parallel for
    for(int i = 0; i < LINHAS; ++i) {
        for(int j = 0; j < COLUNAS; ++j) {
            string res = to_string(m1[i][j] * m2[j][i]);
            resultado[i][j] = res + "(" + to_string(omp_get_thread_num()) + ")";
        }
    }

    for(int i = 0; i < LINHAS; ++i) {
        for(int j = 0; j < COLUNAS; ++j) {
            cout << resultado[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}