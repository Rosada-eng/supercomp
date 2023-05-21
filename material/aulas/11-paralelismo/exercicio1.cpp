#include <chrono>
#include <iostream>
#include <omp.h>
#include <unistd.h>

using namespace std;
double funcao1() {
    sleep(4);
    return 47;
}

double funcao2() {
    sleep(1);
    return -11.5;
}

int main() {
    double res_func1, res_func2;
    int count = 0;
    int nthreads;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

#pragma omp parallel shared(count)
    {
        nthreads = omp_get_num_threads();
#pragma omp master // roda apenas uma vez
        {
            cout << "Eu sou o pai e estou rodando na thread: " << omp_get_thread_num() << endl;
            cout << "Vou chamar funcao1 \n";

            res_func1 = funcao1();
        }

#pragma omp task // roda em paralelo
        {
            cout << "Eu sou o filho e estou rodando na thread: " << omp_get_thread_num() << endl;
            cout << "Vou chamar funcao2 \n";
            count += 1;
            res_func2 = funcao2();
        }
#pragma omp task // roda em paralelo
        {
            cout << "Eu sou o filho e estou rodando na thread: " << omp_get_thread_num() << endl;
            cout << "Vou chamar funcao2 \n";
            count += 1;
            res_func2 = funcao2();
        }
#pragma omp task // roda em paralelo
        {
            cout << "Eu sou o filho e estou rodando na thread: " << omp_get_thread_num() << endl;
            cout << "Vou chamar funcao2 \n";
            count += 1;
            res_func2 = funcao2();
        }
    }

    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    chrono::duration<double> tempo_exec = chrono::duration_cast<chrono::duration<double>>(end - begin);

    cout << "Chamei a funcao2 " << count << " vezes\n"
         << "Número de threads: " << nthreads << endl
         << "Uma para cada thread. Independente de qual estivesse disponível" << endl;
    // count = 3*2
    cout << "Tempo de execução: " << tempo_exec.count() << " segundos" << endl;

    std::cout << res_func1 << " " << res_func2 << "\n";
}
