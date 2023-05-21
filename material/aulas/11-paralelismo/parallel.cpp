#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

double aproxima_pi_leibniz_parallel_2threads(int n) {
    double pi_ = 0.0;

    // Especifica omp para utilizar 2 threads
    omp_set_num_threads(2);

#pragma omp parallel shared(pi_)
    {
        // Cada thread calcula uma parte da série
        int tid = omp_get_thread_num();
        int nthreads = omp_get_num_threads();

        printf("Thread %d de %d\n", tid, nthreads);

        double pi_local = 0.0;
        int init = tid * (n / nthreads);
        int end = (tid + 1) * (n / nthreads);

        printf("Thread %d calcula de %d a %d\n", tid, init, end);

        for (int i = init; i < end; i++) {
            pi_local += pow(-1, i) / (2 * i + 1);
        }

        // Soma os resultados parciais
        pi_ += pi_local;
    }

    pi_ *= 4;

    return pi_;
}

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

double aproxima_pi_leibniz_serie(int n) {
    double pi_ = 0.0;

    for (int i = 0; i < n; i++) {
        pi_ += pow(-1, i) / (2 * i + 1);
    }

    pi_ *= 4;

    return pi_;
}

int main() {
    int n;
    n = 1000000000;
    // cout << "informe um valor n para série:" << endl;
    // cin >> n;

    chrono::steady_clock::time_point start_exec = chrono::steady_clock::now();
    double pi_ = aproxima_pi_leibniz_parallel(n);
    chrono::steady_clock::time_point end_exec = chrono::steady_clock::now();

    // set precision to 10 decimal places

    cout.precision(10);
    cout << "PI: " << pi_ << endl;

    auto exec_time_us = chrono::duration_cast<chrono::microseconds>(end_exec - start_exec).count();

    double exec_time = exec_time_us / 1000000.0;

    cout << "TEMPO DE EXECUÇÃO: " << exec_time << " s" << endl;

    return 0;
}