#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct item {
    int id;
    double peso;
    double valor;
};

void sort_by_value(vector<item> &itens) {
    sort(itens.begin(), itens.end(), [](item a, item b) {
        return a.valor > b.valor;
    });
}

void sort_by_weight(vector<item> &itens) {
    sort(itens.begin(), itens.end(), [](item a, item b) {
        return a.peso < b.peso;
    });
}

int main() {
    int n_total;
    double capacidade;

    cin >> n_total;
    cin >> capacidade;

    vector<item> itens;

    double w;
    double v;
    for (int i = 0; i < n_total; i++) {
        cin >> w;
        cin >> v;
        itens.push_back({i, w, v});
    }

    // sort_by_value(itens);

    sort_by_weight(itens);

    double peso;
    double valor;
    int n_selecionados = 0;

    vector<item> itens_selecionados;
    for (auto i : itens) {
        if (peso + i.peso <= capacidade) {
            peso += i.peso;
            valor += i.valor;
            n_selecionados++;

            itens_selecionados.push_back(i);
        }
    }

    cout << "Peso: " << peso << " Valor: " << valor << " Qtd: " << n_selecionados << endl;

    for (auto i : itens_selecionados) {
        cout << "- " << i.id << " P: " << i.peso << " V: " << i.valor << endl;
    }
    cout << endl;

    return 0;
}