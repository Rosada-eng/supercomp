#include <iostream>
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

using namespace std;

int main() {
    thrust::host_vector<double> h_APPL;
    thrust::host_vector<double> h_MCSF;

    double v1, v2;

    while (cin >> v1 >> v2) {
        h_APPL.push_back(v1);
        h_MCSF.push_back(v2);
    }

    thrust::device_vector<double> d_APPL(h_APPL);
    thrust::device_vector<double> d_MCSF(h_MCSF);

    thrust::device_vector<double> d_diff(d_APPL.size());

    thrust::transform(d_APPL.begin(), d_APPL.end(), d_MCSF.begin(), d_diff.begin(), thrust::minus<double>());

    double mean_diff = thrust::reduce(d_diff.begin(), d_diff.end(), 0.0, thrust::plus<double>()) / d_diff.size();

    cout << "Mean difference: " << mean_diff  << endl;

    //! calcular o desvio padrão das difrenças

    thrust::device_vector<double> mean_diff_vector(d_diff.size(), mean_diff);

    // device_vector (x - u)
    thrust::device_vector<double> d_diff_to_mean(d_diff.size(), 0.0);

    thrust::transform(d_diff.begin(), d_diff.end(),
                     mean_diff_vector.begin(),
                     d_diff_to_mean.begin(),
                     thrust::minus<double>());

    thrust::host_vector<double> h_diff_to_mean(d_diff_to_mean);

    thrust::device_vector<double> d_diff_to_mean2(d_diff_to_mean);
    // (x-u)²
    thrust::transform(d_diff_to_mean.begin(), d_diff_to_mean.end(),
                    d_diff_to_mean2.begin(),
                    thrust::square<double>());

    // somatório (x-u)²
    double sum_square_dif = thrust::reduce(d_diff_to_mean2.begin(), d_diff_to_mean2.end(), 0.0, thrust::plus<float>()) / d_diff_to_mean2.size();

    double std_dev = pow(sum_square_dif, 0.5) ;

    cout << "Desvio Padrão: " << std_dev << endl;


    return 0;
}