#include <omp.h>
#include <random>
#include <iostream>
#include <time.h>

using namespace std;

#define TAMANHO 10


float vetor[TAMANHO];
float resultado = 0;

void inicia_vetor() {
    random_device dev;
    mt19937 rng(dev());
    uniform_int_distribution<mt19937::result_type> dist6(0,TAMANHO*3);
    for(int i = 0; i < TAMANHO; ++i) {
        vetor[i] = dist6(rng);
    }
}

int main(int argc, char *argv[]) {
    double inicio, fim;
    inicia_vetor();
    omp_set_num_threads(2);
    cout << omp_get_num_threads();

    inicio = (double) clock() / CLOCKS_PER_SEC;

    #pragma omp parallel for
    for(int i = 0; i < TAMANHO; ++i) {
        resultado = resultado + vetor[i];
    }
    fim = (double) clock() / CLOCKS_PER_SEC;

    cout << "Tempo de execução: " << (fim - inicio) << endl;
    return 0;
}