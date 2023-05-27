#include <chrono>
#include <fstream>
#include <iostream>
#include <math.h>
#include <omp.h>
#include <random>
#include <vector>

using namespace std;

double calcula_intervalo_tempo_s_owp(auto (*funcao)(int), auto *global_answer, int arg) {
    // TODO: Altere o arg conforme necessário para o exercício
    double init_time = omp_get_wtime();
    *global_answer = funcao(arg);
    double final_time = omp_get_wtime();
    return final_time - init_time;
}

double calcula_intervalo_tempo_s_chrono(auto (*funcao)(int), auto *global_answer, int arg) {
    chrono::steady_clock::time_point start_exec = chrono::steady_clock::now();
    // TODO: Caso necessário, altere para o retorno ser numa variável global
    *global_answer = funcao(arg);
    chrono::steady_clock::time_point end_exec = chrono::steady_clock::now();

    auto exec_time_us = chrono::duration_cast<chrono::microseconds>(end_exec - start_exec).count();

    double exec_time = exec_time_us / 1000000.0;

    cout << "TEMPO EXECUCAO: " << exec_time << endl;

    return exec_time;
}

double pi_montecarlo_serie(int n) {
    double sum = 0.0;
    int N = n;
    int SEED;
    default_random_engine generator;
    vector<double> points;

    /*
        !! Partes CRÍTICAS:
        - sum += 1 (paralelizável)
        ! get_random_coord --> a parte aleatória depende da SEQUÊNCIA que é executável (serial)
        --> estamos utilizando um SEED fixo.

    */
#pragma omp parallel num_threads(8) private(SEED, count, points) shared(sum)
    {
        SEED = omp_get_thread_num();
        default_random_engine generator(SEED);
        uniform_real_distribution<double> distribution(0.0, 1.0);

#pragma omp for reduction(+ : sum)
        // Aqui, o omp fará a divisão dos dados entre as threads. Cada thread tratará N/NUM_THREADS dados
        for (int i = 0; i < N; i++) {
            /* a cada interação, vamos criar um novo gerador de números aleatórios
            e sortear novos números a partir deles.
            * 1) O que acontece se usarmos o mesmo seed em todas iterações?
            *  --> obteremos sempre os mesmos números! (o 1º da sequência gerada por aquele SEED)
            * 2) Vamos fazer o SEED depender da iteração
            * == Resultado: PI:3.14104 em 4.02603 s
            ! PROBLEMA: -> Não temos uma SEQUÊNCIA aleatória. Apenas o 1º número de cada sequência, gerada por um SEED diferente
            * Como só pegar o primeiro número de cada RNGs não garante que a sequência gerada seja indistinguível de
            * uma sequência aleatória, podemos abordar o problema de outra forma:
            * 3) Vamos fazer cada Thread gerar N/NUM_THREAD números aleatórios
            */

            double x = distribution(generator); // omp section -> x²
            double y = distribution(generator); // omp section -> y²

            points.push_back(x);
            points.push_back(y);

            if (pow(x, 2) + pow(y, 2) <= 1) {
                sum += 1;
            }
        }
    }

    double pi = 4 * sum / N;

    return pi;
}

int main() {
    int N = 100000;
    double pi;

    calcula_intervalo_tempo_s_chrono(pi_montecarlo_serie, &pi, N);

    cerr << "PI: " << pi << "\n";

    return 0;
}
