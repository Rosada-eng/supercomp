#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/functional.h>
#include <iostream>
#include <chrono>
#include <cstdlib>
#include <cmath>
#include <random>
#include <algorithm>
#include <iomanip>


using namespace std;

// obs.: Já existe um transform para elevar ao quadrado (square),
// mas vamos implementar um functor para praticar

struct my_square 
{
    __host__ __device__
    float operator()(const float& x) {
        return x*x;
    }
};

float magnitude(thrust::host_vector<float> &v) {
    // copie os vetores para a GPU
    thrust::device_vector<float> d_numbers = v;

    // eleve ao quadrado os elementos do vetor
    thrust::transform(
        d_numbers.begin(), d_numbers.end(),
        d_numbers.begin(), // onde vai armazenar o retorno da função
        my_square()
    );

    float sum = thrust::reduce(
        d_numbers.begin(), d_numbers.end(),
        0.0,
        thrust::plus<float>()
    );

    float norma = sqrt(sum);

    return norma;

}

int main(int argc, char** argv) {
    if (argc != 2) {
        cerr << argv[0] << ": numero invalido de argumentos\n"; 
        cerr << "uso: " << argv[0] << "  tamanho do vetor\n"; 
        return 1;
    }

    // numero de elementos
    int N = atoi(argv[1]); 
    chrono::steady_clock::time_point t1, t2;

    // Geração
    // ---------------------------------------------
    t1 = chrono::steady_clock::now();

    // gere os vetores de tamanho N
    thrust::host_vector<float> h_numbers(N);
    thrust::generate(h_numbers.begin(), h_numbers.end(), rand);
    
    t2 = chrono::steady_clock::now();
    cout << "tempo de geracao: " << chrono::duration_cast<chrono::duration<double> >(t2 - t1).count() << "s" << endl;
    // ---------------------------------------------


    // Norma
    // ---------------------------------------------
    t1 = chrono::steady_clock::now();

    float norma = magnitude(h_numbers);

    t2 = chrono::steady_clock::now();
    cout << "tempo de norma: " << chrono::duration_cast<chrono::duration<double> >(t2 - t1).count() << "s" << endl;
    // ---------------------------------------------

    cout << fixed << setprecision(6);    
    cout << "norma: " << norma << endl;
    

    return 0;

}



