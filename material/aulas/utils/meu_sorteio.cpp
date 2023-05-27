#include <iostream>
#include <random>

using namespace std;

//! para resultados ALEATÓRIOS a cada vez que executar, utilize random_device:
// -> ele pegará o timestamp do sistema para gerar o seed
default_random_engine generator(random_device{}());

//! para resultados REPRODUZÍVEIS a cada vez que executar, utilize o SEED
// int SEED = 13;
// default_random_engine generator(SEED);

double get_random_coord() {
    // Para geração aleatória de Números Reais
    uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(generator);
}

int get_index_between(int min, int max) {
    // Para geração aleatória de Números Inteiros
    uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}
