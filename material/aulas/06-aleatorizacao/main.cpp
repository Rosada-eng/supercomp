#include <algorithm>
#include <iostream>
#include <random>

using namespace std;

int SEED = 10;
default_random_engine generator(SEED);

// Para geração aleatória de Números Inteiros
// uniform_int_distribution<int> distribution(1, 6);

// Para geração aleatória de Números Reais
uniform_real_distribution<double> distribution(0.0, 1.0);

double get_random_coord() {
    return distribution(generator);
}

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

void read_input_items(vector<item> &destiny, int n_total) {
    double w;
    double v;
    for (int i = 0; i < n_total; i++) {
        cin >> w;
        cin >> v;
        destiny.push_back({i, w, v});
    }
}

int main() {
    int n_total;
    double capacidade;

    cin >> n_total;
    cin >> capacidade;

    vector<item> itens;

    // passa array via referência
    read_input_items(itens, n_total);

    // ! SELECIONE A HEURÍSTICA DE ORDENAÇÃO (mais valiosos) OU (menos pesados)
    sort_by_value(itens);
    // sort_by_weight(itens);

    double peso = 0;
    double valor = 0;

    vector<int> ids_selecionados;
    vector<item> itens_selecionados;

    for (int i = 0; i < n_total; i++) {
        double r = get_random_coord();
        item selected;
        if (r > 1 - 0.75) {
            // PROBABILIDADE DE 75%
            // -> usar heurística (seleciona o próximo elemento mais valioso ou mais leve)
            // cout << "heuristica " << r << endl;
            selected = itens[i];
            cout << "heuristica " << selected.id << endl;
        } else {
            // PROBABILIDADE DE 25%
            // seleciona um elemento aleatório dos que não foram analisados
            uniform_int_distribution<int> distribution(i, n_total - 1);
            int random_index = distribution(generator);

            cout << "aleatorio " << random_index << endl;
            selected = itens[random_index];

            // cout << "aleatorio " << r << " " << random_index << endl;

            i--; // retorna um passo para trás -> "não alteramos o elemento"
        }

        // checa se o item selecionado cabe na mochila
        // checa se o item já não foi utilizado
        if ((peso + selected.peso < capacidade) && (find(ids_selecionados.begin(), ids_selecionados.end(), selected.id) == ids_selecionados.end())) {
            // guardar na mochila
            peso += selected.peso;
            valor += selected.valor;

            ids_selecionados.push_back(selected.id);
            itens_selecionados.push_back(selected);
        }
    }

    cout << "Peso: " << peso << " Valor: " << valor << " Qtd: " << itens_selecionados.size() << endl;

    for (auto i : itens_selecionados) {
        cout << "-id: " << i.id << " P: " << i.peso << " V: " << i.valor << endl;
    }

    cout << endl;

    return 0;
}