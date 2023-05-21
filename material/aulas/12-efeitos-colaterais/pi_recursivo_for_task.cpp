#include <iomanip>
#include <iostream>
#include <omp.h>

static long num_steps = 1024l * 1024 * 1024 * 2;

#define MIN_BLK 1024 * 1024 * 256

double sum = 0;
int fork_count = 0;

void pi_r(long Nstart, long Nfinish, double step) {
    /**
     Examinando o código:
     * O código tenta reduzir o tamanho do laço até que seja pequeno o suficiente para processá-lo.
     *
     * Enquanto não é pequeno suficiente, a função é chamada recursivamente com valores menores.
     * A primeira chamada fará outras chamadas recursivas até que o tamanho do laço seja pequeno o suficiente. Só então, processará os dados e aí, sim, chamará o segundo pi_r recursivamente que, por sua vez, fará uma série de chamadas até que o tamanho do laço seja pequeno o suficiente.
     * Essa abordagem é uma espécie de "divisão e conquista".
     * Porém, seriam necessários vários passos até que TODO o processo seja feito.
     *
    */

    /**
     * As oportunidades de paralelismo aparecem em:
     * --- Chamada recursiva das funções pi_r
     *   |- Não precisam ser executadas sequencialmente, visto que não há dependência
     * --- Na execução do laço for
     *
     */

    /**
     * São três níveis de chamadas recursivas:
     *
     */

    long i, iblk;
    if (Nfinish - Nstart < MIN_BLK) {
#pragma omp parallel for reduction(+ : sum)
        for (i = Nstart; i < Nfinish; i++) {
            double x = (i + 0.5) * step;
            sum += 4.0 / (1.0 + x * x);
        }
    } else {
        iblk = Nfinish - Nstart;
#pragma omp task
        {
            pi_r(Nstart, Nfinish - iblk / 2, step);
            fork_count += 1;
        }
#pragma omp task
        {
            pi_r(Nfinish - iblk / 2, Nfinish, step);
        }
    }
}

int main() {
    long i;
    double step, pi;
    double init_time, final_time;
    step = 1.0 / (double)num_steps;
    init_time = omp_get_wtime();
    pi_r(0, num_steps, step);
    pi = step * sum;
    final_time = omp_get_wtime() - init_time;

    std::cout << "for " << num_steps << " steps pi = " << std::setprecision(15) << pi << " in " << final_time << " secs\n";

    std::cout << "fork_count = " << fork_count << "\n";
}
