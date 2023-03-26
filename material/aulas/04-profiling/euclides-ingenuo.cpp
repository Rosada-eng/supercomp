#include <cmath>
#include <iostream>
#include <vector>

typedef std::vector<std::vector<double>> matriz;

void calcula_distancias(matriz &mat, std::vector<double> &x, std::vector<double> &y) {
    int n = x.size();
    for (int i = 0; i < n; i++) {
        std::vector<double> linha;
        for (int j = 0; j < n; j++) {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            linha.push_back((dx * dx + dy * dy));
        }
        mat.push_back(linha);
    }
}

void calcula_distancias2(matriz &mat, std::vector<double> &x, std::vector<double> &y) {
    // Evita calcular uma distância repetida
    // Porém, ainda percorre todo o looping

    int n = x.size();
    for (int i = 0; i < n; i++) {
        std::vector<double> linha;
        for (int j = 0; j < n; j++) {
            if (i <= j) {
                double dx = x[i] - x[j];
                double dy = y[i] - y[j];
                linha.push_back((dx * dx + dy * dy));
            } else {
                linha.push_back(mat[j][i]);
            }
        }
        mat.push_back(linha);
    }
}

void calcula_distancias3(matriz &mat, std::vector<double> &x, std::vector<double> &y) {
    // vamos alocar previamente a matriz
    // calcula efetivamente a quantidade necessária apenas
    int i = 0;
    int j = 0;
    int n = x.size();

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            mat[i][j] = 0.0;
        }
    }

    for (int i = 0; i < n; i++) {
        double dist;
        for (int j = i; j < n; j++) {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            dist = (dx * dx + dy * dy);

            mat[i][j] = dist;
            mat[j][i] = dist;
        }
    }
}

void calcula_distancias4(std::vector<double> &mat, std::vector<double> &x, std::vector<double> &y) {
    // Matriz em Linha M[l ,c]
    // m[i,j] = i * c + j
    int n = x.size();

    mat.resize(n * n);
    // transforma a matriz em um vetor linear

    int i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            // mat[i][j] = 0.0;

            mat[i * n + j] = 0.0;
        }
    }

    for (int i = 0; i < n; i++) {
        double dist;
        for (int j = i; j < n; j++) {
            double dx = x[i] - x[j];
            double dy = y[i] - y[j];
            dist = (dx * dx + dy * dy);

            // mat[i][j] = dist;
            // mat[j][i] = dist;

            mat[i * n + j] = dist;
            mat[j * n + i] = dist;
        }
    }
}

int main() {
    // matriz mat;
    std::vector<double> lin_mat;
    std::vector<double> x, y;
    int n;

    std::cin >> n;
    x.reserve(n);
    y.reserve(n);
    lin_mat.reserve(n * n);
    for (int i = 0; i < n; i++) {
        double xt, yt;
        std::cin >> xt >> yt;
        x.push_back(xt);
        y.push_back(yt);
    }

    calcula_distancias4(lin_mat, x, y);

    // for (auto &linha : mat) {
    //     for (double el : linha) {
    //         std::cout << el << " ";
    //     }
    //     std::cout << "\n";
    // }
    int i = 0;
    for (i; i < lin_mat.size(); i++) {
        std::cout << lin_mat[i] << " ";

        if (i % n == n - 1) {
            std::cout << "\n";
        }
    }

    return 0;
}
