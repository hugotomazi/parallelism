/*
    UNIVALI - Universidade do Vale do Itajaí
    Trabalho desenvolvido para a disciplina de Sistemas Operacionais

    Autor: Hugo Tomazi Busnardo

    Comando para build:
    g++ -pthread -lpthread main.cpp -o build/pthread
*/
#include <iostream>
#include <sys/sysinfo.h>
#include <pthread.h>
#include <random>
#include <time.h>

using namespace std;

#define LINHAS 100
#define COLUNAS 500


int m1[LINHAS][COLUNAS];
int m2[COLUNAS][LINHAS];
int resultado[LINHAS][COLUNAS];

void *execThread(void *params);

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
    int qtdTHREADS = get_nprocs_conf();
    
    initMatrix();

    inicio = (double) clock() / CLOCKS_PER_SEC;
    
    pthread_t tid[qtdTHREADS];
    pthread_attr_t attr[qtdTHREADS];

    int thread_params[qtdTHREADS][2];
    int div = LINHAS / qtdTHREADS;

    for(int i = 0; i < qtdTHREADS; ++i) {
        thread_params[i][0] = (i * div);
        if(i == qtdTHREADS - 1 && LINHAS % 2 != 0) {
            thread_params[i][1] = (i * div) + div + 1;
        } else {
            thread_params[i][1] = (i * div) + div;
        }

        pthread_attr_init(&attr[i]);
        pthread_create(&tid[i], &attr[i], execThread, thread_params[i]);
    }

    for(int i = 0; i < qtdTHREADS; ++i) {
        pthread_join(tid[i], NULL);
    }

    fim = (double) clock() / CLOCKS_PER_SEC;

    cout << "Tempo de execução: " << (fim - inicio) << endl;
    return 0;
}

void *execThread(void *params) {
    int *newParams = (int *) params;

    for(int i = newParams[0]; i < newParams[1]; ++i) {
        for(int j = 0; j < COLUNAS; ++j) {
            resultado[i][j] = m1[i][j] * m2[j][i];
        }
    }
    pthread_exit(0);
}