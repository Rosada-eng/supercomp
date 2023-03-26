#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

float calcula_distancia(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void calcula_matriz_distancias(vector<vector<float>> pontos, vector<vector<float>> &matriz_distancias) {
    int i = 0;
    while (i < pontos.size()) {
        vector<float> linha;
        int j = 0;
        while (j < pontos.size()) {
            float distancia = calcula_distancia(pontos[i][0], pontos[i][1], pontos[j][0], pontos[j][1]);
            linha.push_back(distancia);
            j++;
        }
        matriz_distancias.push_back(linha);
        i++;
    }
}

int main() {
    int matriz_size;
    // cout << "Digite o numero de pontos: ";
    cin >> matriz_size;

    vector<vector<float>> pontos;
    int i = 0;
    while (i < matriz_size) {
        vector<float> ponto;
        float x, y;
        // cout << "Digite as coordenadas x e y do ponto " << i << ": ";
        cin >> x >> y;
        ponto.push_back(x);
        ponto.push_back(y);
        pontos.push_back(ponto);
        i++;
    }

    vector<vector<float>> matriz_distancias;
    // i = 0;
    // while (i < matriz_size) {
    //     vector<float> linha;
    //     int j = 0;
    //     while (j < matriz_size) {
    //         float distancia = calcula_distancia(pontos[i][0], pontos[i][1], pontos[j][0], pontos[j][1]);
    //         linha.push_back(distancia);
    //         j++;
    //     }
    //     matriz_distancias.push_back(linha);
    //     i++;
    // }

    calcula_matriz_distancias(pontos, matriz_distancias);

    i = 0;
    while (i < matriz_size) {
        int j = 0;
        cout.precision(2);
        while (j < matriz_size) {
            cout << fixed << matriz_distancias[i][j] << " ";
            j++;
        }
        cout << endl;
        i++;
    }

    return 0;
}