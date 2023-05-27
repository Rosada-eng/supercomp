#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/generate.h>
#include <thrust/copy.h>
#include <iostream>

using namespace std;

struct saxpy 
{
    int alpha;      // argumento a ser armazenado internamente pela função

    // declaração da função : atribuição dos parâmetros
    saxpy(int a_) : alpha(a_) {};

    // Indica ao Compilador o alvo de compilação
    __host__ __device__

    // operator
    float operator()(const float &x, const float& y) {
        return alpha*x + y;
    };

    // obs.: Utilize float para ocupar menos espaço na memória. 
    // Se quiser precisão, utilize double ("double precision")
};




int main(int argc, char* argv[]){
    if (argc != 3) {
        cerr << "Número incorreto de argumentos" << endl;

        return 1;
    }

    int N = atoi(argv[1]);
    int m = atoi(argv[2]);

    // gerar números aleatórios
    thrust::host_vector<int> a(N);
    thrust::host_vector<int> b(N);
    thrust::host_vector<int> c(N);

    // popula os vetores com números aleatórios
    thrust::generate(a.begin(), a.end(), rand);
    thrust::generate(b.begin(), b.end(), rand);

    // transforma para vetores na GPU
    thrust::device_vector<int> d_a = a;
    thrust::device_vector<int> d_b = b;
    
    // aplica transformação saxpy
    thrust::transform(
        d_a.begin(), d_a.end(),
        d_b.begin(), d_b.end(),
        saxpy(m));  // o resultado é armazenado em d_b

    thrust::copy(
        d_b.begin(), d_b.end(),
        c.begin());

    for (int i=0; i<N; i++) {
        cout << setw(6) << c[i] << " = "
        << setw(2) << m
        << "*" << setw(5) << a[i]
        << "+" << setw(5) << b[i]
        << endl;
    }

    return 0;
}