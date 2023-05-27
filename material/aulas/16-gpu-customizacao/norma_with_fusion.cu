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

/**
// <> TRANSFORM-REDUCE
thrust::transform_reduce( v.begin(), v.end(), unary_op, init, binary_op)
    // unary_op: função unária = SQUARE(X)
    // init: valor inicial 0.0
    // binary_op: função binária = PLUS (X,Y)
    // retorna o resultado da operação binária
/

//<> UNARY OP
struct my_square 
{
    __host__ __device__
    float operator()(const float& x) {
        return x*x;
    }
}; 

// <> BINARY OP -- plus<float>()

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

float magnitude_tr(thrust::host_vector<float> &v) {
    // copie os vetores para a GPU
    thrust::device_vector<float> d_numbers = v;

    float soma_quadratica = thrust::transform_reduce(
        d_numbers.begin(), d_numbers.end(),
        my_square(), // unary op
        0.0,
        thrust::plus<float>() // binary op
    );

    float norma = sqrt(soma_quadratica);

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


    //! Norma c/ transform_reduce
    // ---------------------------------------------
    t1 = chrono::steady_clock::now();

    // float norma = magnitude(h_numbers);
    float norma = magnitude_tr(h_numbers);
    


    t2 = chrono::steady_clock::now();
    cout << "tempo de norma c/ transform_reduce: " << chrono::duration_cast<chrono::duration<double> >(t2 - t1).count() << "s" << endl;
    // ---------------------------------------------

    cout << fixed << setprecision(6);    
    cout << "norma: " << norma << endl;
    

    return 0;

}



