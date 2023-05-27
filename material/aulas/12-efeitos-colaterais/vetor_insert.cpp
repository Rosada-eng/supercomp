#include <iostream>
#include <omp.h>
#include <unistd.h>
#include <vector>

double conta_complexa(int i) {
    return 2 * i;
}

int main() {
    int N = 1000;
    std::vector<double> vec[N];

    for (int i = 0; i < N; i++) {
        vec[i] = 0.0;
    }

    double init_time = omp_get_wtime();

    /**
     * @ Implementação ruim! Popular um vetor com push_back
     * A melhor solução seria inicializar um vetor e, depois,
     * alterar seus valores conforme a posição i, tomando o respectivo
     * cuidado para fazer escrita somente de uma vez no vetor vec.
     * */

    //@ RUIM!
    // #pragma omp parallel for shared(vec, N) private(i) default(none)
    //     for (i = 0; i < N; i++) {
    //         double x = conta_complexa(i);
    // #pragma omp critical
    //         vec.push_back(x);
    //     }

    //* MELHOR!

    // preenche o vetor com a função complexa
    // #pragma omp parallel for shared(vec, N) private(i) default(none)
    //     for (i = 0; i < N; i++) {
    //         double x = conta_complexa(i);
    // #pragma omp critical
    //         vec[i] = x;
    //     }
    /**
     * Ao separar a função conta_complexa() para fora do omp critical,
     * o tempo reduziu praticamente pela metade.
     * Isso é notório, pois, se as duas operações estão juntas,
     * a thread precisa realizar 2 steps antes de liberar o recurso para a próxima.
     *
     * !! A quantidade de operações dentro do omp critical deve ser MÍNIMA!
     */

    double final_time = omp_get_wtime();

    for (int i = 0; i < N; i++) {
        std::cout << vec[i] << " ";
    }

    std::cout << "\nTEMPO EXECUCAO: " << final_time - init_time << "\n";

    return 0;
}
