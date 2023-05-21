#include <algorithm>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>

using namespace std;

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
    double pi_ = aproxima_pi_leibniz_serie(n);
    chrono::steady_clock::time_point end_exec = chrono::steady_clock::now();

    // set precision to 10 decimal places

    cout.precision(10);
    cout << "PI: " << pi_ << endl;

    auto exec_time_us = chrono::duration_cast<chrono::microseconds>(end_exec - start_exec).count();

    double exec_time = exec_time_us / 1000000.0;

    cout << "TEMPO DE EXECUÇÃO: " << exec_time << " s" << endl;

    return 0;
}