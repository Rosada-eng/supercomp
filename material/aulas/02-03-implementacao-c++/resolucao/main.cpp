#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

float calcula_serie(int n) {
    float soma = 0;
    int i = 0;

    while (i <= n) {
        soma += (1.0 / pow(2, i));
        i++;
    }

    return soma;
}

float calcula_media(vector<double> vec, int n) {
    float soma = 0;
    int i = 0;

    while (i < n) {
        soma += vec[i];
        i++;
    }

    return soma / n;
}

float calcula_variancia(vector<double> vec, int n) {
    float media = calcula_media(vec, n);
    float soma = 0;
    int i = 0;

    while (i < n) {
        soma += pow(vec[i] - media, 2);
        i++;
    }

    return soma / n;
}

int main() {
    int n;
    cout << "Digite o valor de n: ";
    cin >> n;

    vector<double> vec;
    int i = 0;
    float input;
    while (i < n) {
        cout << "Digite o valor " << i << ": ";
        cin >> input;
        vec.push_back(input);
        i++;
    }

    float media = calcula_media(vec, n);
    float variancia = calcula_variancia(vec, n);

    cout << "Media: " << setprecision(14) << media << endl;
    cout << "Variancia: " << setprecision(14) << variancia << endl;

    return 0;
}
