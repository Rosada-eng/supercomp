#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
    thrust::host_vector<double> h_APPL;
    thrust::host_vector<double> h_MSFT;

    double v1, v2;

    while (cin >> v1 >> v2) {
        h_APPL.push_back(v1);
        h_MSFT.push_back(v2);
    }

    chrono::steady_clock::time_point start_exec = chrono::steady_clock::now();
    // --
    thrust::device_vector<double> d_APPL(h_APPL);
    thrust::device_vector<double> d_MSFT(h_MSFT);

    thrust::device_vector<double> diffs(d_APPL.size(), 0.0);

    // diffs = APPL - MSFT
    thrust::transform(d_APPL.begin(), d_APPL.end(), d_MSFT.begin(), diffs.begin(), thrust::minus<double>());
    // mean_diff = mean(diffs)
    double mean_diff = thrust::reduce(diffs.begin(), diffs.end(), 0.0, thrust::plus<double>()) / diffs.size();
    // --
    chrono::steady_clock::time_point end_exec = chrono::steady_clock::now();

    auto exec_time_us = chrono::duration_cast<chrono::microseconds>(end_exec - start_exec).count();

    double exec_time = exec_time_us / 1000000.0;

    cout << "Mean difference: " << mean_diff << endl;
    cout << "Exec time: " << exec_time << endl;

    //! CALCULA VARIÂNCIA DAS DIFERENÇAS

    thrust::host_vector<double> h_diffs(diffs);

    // opera (x - mean_diff)
    thrust::transform(diffs.begin(), diffs.end(), thrust::constant_iterator<double>(mean_diff), h_diffs.begin(), thrust::minus<double>());

    // eleva ao quadrado
    thrust::host_vector<double> h_diffs2(h_diffs);

    thrust::transform(h_diffs.begin(), h_diffs.end(), h_diffs2.begin(), thrust::square<double>());

    // soma tudo
    double sum_diffs = thrust::reduce(h_diffs2.begin(), h_diffs2.end(), 0.0, thrust::plus<double>());

    // divide pelo tamanho
    double variance = sum_diffs / diffs.size();

    cout << "Variance: " << variance << endl;

    return 0;
}