#include <chrono>
#include <iostream>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

int main() {
    // cria um vetor no host e armazena os valores das ações

    thrust::host_vector<double> h_vec;
    double price;
    while (std::cin >> price) {
        if (price) {
            h_vec.push_back(price);
        }
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    // cria um vetor no device e copia os valores do vetor do host
    thrust::device_vector<double> d_vec(h_vec);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Tempo de copia: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " us" << std::endl;

    //>> REDUCE <<//
    //! Realiza operação em UM VETOR
    double max = thrust::reduce(d_vec.begin(), d_vec.end(), -1.0, thrust::maximum<double>());

    std::cout << "Máximo: " << max << std::endl;

    //** Exercícios **//

    //* Preço médio
    double total_sum = thrust::reduce(d_vec.begin(), d_vec.end(), 0.0, thrust::plus<double>());

    int n = d_vec.size();

    double avg = total_sum / (double)n;

    std::cout << "Preço médio: " << avg << std::endl;

    //* Preço médio no último ano (últimos 365 dias)
    double total_sum_last_year = thrust::reduce(d_vec.end() - 365, d_vec.end(), 0.0, thrust::plus<double>());

    double avg_last_year = total_sum_last_year / 365.0;

    std::cout << "Preço médio no último ano: " << avg_last_year << std::endl;

    //* Maior e Menor Preço nos Últimos 10 anos
    double max_last_10_years = thrust::reduce(d_vec.begin(), d_vec.end(), -1.0, thrust::maximum<double>());
    double min_last_10_years = thrust::reduce(d_vec.begin(), d_vec.end(), 1000000, thrust::minimum<double>());

    std::cout << "Maior preço nos últimos 10 anos: " << max_last_10_years << std::endl;
    std::cout << "Menor preço nos últimos 10 anos: " << min_last_10_years << std::endl;

    //* Maior e Menor Preço no Último ano
    double max_last_year = thrust::reduce(d_vec.end() - 365, d_vec.end(), -1.0, thrust::maximum<double>());
    double min_last_year = thrust::reduce(d_vec.end() - 365, d_vec.end(), 1000000, thrust::minimum<double>());

    std::cout << "Maior preço no último ano: " << max_last_year << std::endl;
    std::cout << "Menor preço no último ano: " << min_last_year << std::endl;

    return 0;
}