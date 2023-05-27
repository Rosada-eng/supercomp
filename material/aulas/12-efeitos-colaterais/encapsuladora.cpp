#include <chrono>
#include <fstream>
#include <iostream>
#include <math.h>
#include <omp.h>

using namespace std;

double aproxima_pi_leibniz_parallel(int n) {
    double pi_ = 0.0;
    int i = 0;
#pragma omp parallel num_threads(8)
    {
#pragma omp for reduction(+ : pi_)

        // Cada thread calcula uma parte da série
        for (i = 0; i < n; i++) {
            pi_ += pow(-1, i) / (2 * i + 1);
        }

        int tid = omp_get_thread_num();

        printf("I'm thread %d. My calc is: %f\n", tid, pi_);
    }
    pi_ *= 4;

    return pi_;
}

double calcula_intervalo_tempo_s_owp(auto (*funcao)(int), int arg) {
    // TODO: Altere o arg conforme necessário para o exercício
    double init_time = omp_get_wtime();
    funcao(arg);
    double final_time = omp_get_wtime();
    return final_time - init_time;
}

double calcula_intervalo_tempo_s_chrono(auto (*funcao)(int), int arg) {
    // TODO: Altere o arg conforme necessário para o exercício

    chrono::steady_clock::time_point start_exec = chrono::steady_clock::now();
    // TODO: Caso necessário, altere para o retorno ser numa variável global
    double pi_ = funcao(arg);
    chrono::steady_clock::time_point end_exec = chrono::steady_clock::now();

    auto exec_time_us = chrono::duration_cast<chrono::microseconds>(end_exec - start_exec).count();

    double exec_time = exec_time_us / 1000000.0;

    return exec_time;
}

int main() {

    // double delta_t = calcula_intervalo_tempo_s_owp(aproxima_pi_leibniz_parallel, 1000000000);
    double delta_t = calcula_intervalo_tempo_s_chrono(aproxima_pi_leibniz_parallel, 1000000000);
    printf("Tempo de execução: %f\n", delta_t);
    return 0;
}
