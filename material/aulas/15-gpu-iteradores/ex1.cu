#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <iostream>

using namespace std;

struct has_raised
    {
        __device__
        bool operator() (const float &x) const
        {
            return x > 0;
        }
    };

struct is_negative
    {
        __device__
        bool operator()(const float &x) const
        {
            return x<0;
        }
    };

int main(){
    thrust::host_vector<float> h_GOOG;
    float v;

    while (cin >> v) {
        h_GOOG.push_back(v);
    }

    // crie um vetor contendo a diferença entre o dia atual e o anterior

    thrust::device_vector<float> d_GOOG(h_GOOG);
    thrust::device_vector<float> ganho_diario(h_GOOG.size(), 0.0);

    // d = g[i+1] - g[i]
    thrust::transform(
        d_GOOG.begin() + 1 , d_GOOG.end(),
        d_GOOG.begin(),
        ganho_diario.begin(),
        thrust::minus<float>()
    );

    //TODO:  1- Contar quantas vezes o valor subiu
    //  count_if | operator (has_raised)

    

    int raised_amount = thrust::count_if(
        ganho_diario.begin(),
        ganho_diario.end(),
        has_raised()
    );

    cout << "Qtd subidas: " << raised_amount << endl;

    //TODO:  2- Calcular o valor médio
    // -> Substitui todos os valores negativos por Zero.

    
    
    is_negative negative_pred;
    
    thrust::replace_if(
        ganho_diario.begin(),
        ganho_diario.end(),
        negative_pred,
        0
    );

    // -> Reduz o vetor, calculando a soma.
    float raised_sum = thrust::reduce(
                            ganho_diario.begin(),
                            ganho_diario.end(),
                            0.0,
                            thrust::plus<float>()
                        );

    
    // -> Calcula a média fazendo soma_pos / n_pos;
    float raised_mean = raised_sum / raised_amount;

    cout << "Média de subida: " << raised_mean << endl;



    return 0;
}