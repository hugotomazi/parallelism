/*
    UNIVALI - Universidade do Vale do Itajaí
    Trabalho desenvolvido para a disciplina de Sistemas Operacionais

    Autor: Rafael dos Santos

    Comando para build:
    g++ -pthread -lpthread main.cpp -o build/pthread
*/

#include <iostream>
#include <sys/sysinfo.h>
#include <pthread.h>
#include <random>
#include <time.h>

using namespace std;

#define TAMANHO 150000

float vetor[TAMANHO];
float resultado = 0.0;

void *execThread(void *params);

void inicia_vetor() {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0,TAMANHO*3);
    for(int i = 0; i < TAMANHO; ++i) {
        vetor[i] = dist6(rng);
    }
    for (int i = 0; i < TAMANHO; ++i){
        cout << "Valor " << i << ": " << vetor[i] << endl;
    }
}

int main(int argc, char *argv[]) {
    double inicio, fim;
    int qtdTHREADS = get_nprocs_conf();
    
    inicia_vetor();

    inicio = (double) clock() / CLOCKS_PER_SEC;
    
    pthread_t tid[qtdTHREADS];
    pthread_attr_t attr[qtdTHREADS];

    int thread_params[qtdTHREADS][2];
    int div = TAMANHO / qtdTHREADS;

    for(int i = 0; i < qtdTHREADS; ++i) {
        thread_params[i][0] = (i * div);
        if(i == qtdTHREADS - 1 && TAMANHO % 2 != 0) {
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
        resultado = resultado + vetor[i];
    }

    cout << "Resultado: " << resultado << endl;

    pthread_exit(0);
}