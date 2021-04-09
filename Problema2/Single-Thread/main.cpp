#include <iostream>
#include <time.h>
#include <random>

using namespace std;

#define TAMANHO 150000

int vetor[TAMANHO];
int resultado = 0;

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

    inicio = (double) clock() / CLOCKS_PER_SEC;
    for(int i = 0; i < TAMANHO; ++i) {
        resultado = resultado + vetor[i];
    }
    fim = (double) clock() / CLOCKS_PER_SEC;

    cout << "Tempo de execução: " << (fim - inicio) << endl;
    return 0;
}