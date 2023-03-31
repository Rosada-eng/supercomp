#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct movie {
    int id;
    int start;
    int end;
    int category;
};

void read_movies_booking(int size, vector<movie> &book) {
    for (int i = 0; i < size; i++) {
        movie m;
        m.id = i;
        cin >> m.start;
        cin >> m.end;
        cin >> m.category;

        if (m.end < m.start) {
            m.end += 24; // acaba no dia seguinte
        }

        book.push_back(m);
    }
}

void sort_book_by_ending_time(vector<movie> &book) {
    sort(book.begin(), book.end(), [&](movie &m1, movie &m2) { return m1.end < m2.end; });
}

int main() {
    int n;
    int m;

    cin >> n;
    cin >> m;

    vector<int> max_filmes; // lista de máximo por categoria

    max_filmes.push_back(0);
    for (int j = 1; j < m + 1; j++) {
        int max = 0;
        cin >> max;

        max_filmes.push_back(max);
    }

    vector<movie> book; // lista de filmes

    read_movies_booking(n, book); // lê os filmes e preenche-os em book

    sort_book_by_ending_time(book);

    // criar matriz de zeros
    vector<int> linha;
    linha.reserve(m + 1);

    vector<vector<int>> matriz;
    matriz.reserve(n + 1);

    // preenche linha de zeros
    for (int j = 0; j < m + 1; j++) {
        linha.push_back(0);
    }

    // preenche linhas da matriz com linha de zeros
    for (int i = 0; i < n + 1; i++) {
        matriz.push_back(linha);
    }

    // preenche a primeira linha da matriz com o máximo de cada categoria
    for (int j = 1; j < m + 1; j++) {
        matriz[0][j] = max_filmes[j];
    }

    // preenche o restante das linhas da matriz
    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            if (book[i].category != j) {
                matriz[i][j] = matriz[i - 1][j];
                // repete o valor da linha de cima (filme da categoria j não foi consumido)
                // o valor da linha corresponde ao saldo atual de filmes da categoria que podem ser assistidos
            } else {
                int last = i - 1;

                while ((last > 0) && (book[last].end > book[i].start)) {
                    last -= 1;
                }

                // reduz o índice de last até encontrar o último filme que acaba antes do próximo começar

                int max_count = 0;

                int lim = min(matriz[last][j - 1], book[i].end - book[i].start - 1);

                for (int k = 0; k < lim; k++) {
                    max_count = max(max_count, matriz[last][j - 1 - k] + k + 1);
                }

                matriz[i][j] = max(matriz[i - 1][j], max_count);
            }
        }
    }

    cout << matriz[n][m] << endl;

    return 0;
}
