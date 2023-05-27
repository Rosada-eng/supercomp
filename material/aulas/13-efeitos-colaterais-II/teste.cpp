#include <iostream>
#include <omp.h>

int main() {
    double sum = 0.0;
    int i;
#pragma omp parallel num_threads(8) shared(sum) private(i)
    {
        int tid = omp_get_thread_num();
        printf("I'm thread %d\n", tid);

#pragma omp for reduction(+ : sum)
        for (i = 0; i < 100; i++) {
            // generate a random number

            sum += 1;
        }

        printf("I'm thread %d. My sum is: %f\n", tid, sum);
    }

    return 0;
}