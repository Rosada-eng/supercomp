#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct item {
    int id;
    double peso;
    double valor;
};

double get_probability() {
    // srand (time(NULL)) gera um seed diferente para cada vez que executar o programa
    srand(time(NULL));

    // ! Para garantir reprodutibilidade, altere o seed para um valor FIXO
    unsigned int seed = rand();

    // tornar o engine statico garante que a geração de números aleatórios a cada chamda de função
    static default_random_engine generator(seed);
    static uniform_real_distribution<double> distribution(0.0, 1.0);

    return distribution(generator);
}

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

double calculate_fitting(vector<item> &itens, vector<int> &ids_selecionados) {
    int n = itens.size();
    double valor = 0;

    for (int i = 0; i < n; i++) {
        if (ids_selecionados[i] == 1) {
            valor += itens[i].valor;
        }
    }

    return valor;
}

void gera_mochila_aleatoria(vector<item> &itens, vector<int> &ids_selecionados, double capacidade) {
    int n_total = itens.size();

    double peso = 0;

    for (int i = 0; i < n_total; i++) {
        double prob = get_probability();

        if (prob < 0.5) {
            // objeto selecionado
            if (peso + itens[i].peso <= capacidade) {
                // selecionado e cabe na
                peso += itens[i].peso;

                ids_selecionados.push_back(1);
            } else {

                ids_selecionados.push_back(0);
                continue;
            }

        } else {
            ids_selecionados.push_back(0);
        }
    }

    for (uint i = 0; i < ids_selecionados.size(); i++) {
        cout << ids_selecionados[i] << " ";
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

    vector<vector<int>> mochilas_geradas;
    vector<double> valores;

    for (int i = 0; i < 10; i++) {
        vector<int> ids_selecionados;
        gera_mochila_aleatoria(itens, ids_selecionados, capacidade);

        mochilas_geradas.push_back(ids_selecionados);
        double valor_total = calculate_fitting(itens, ids_selecionados);
        cout << "Valor total: " << valor_total << endl;
        valores.push_back(valor_total);
    }

    int idx_melhor_mochila = max_element(valores.begin(), valores.end()) - valores.begin();

    cout << "Melhor mochila: " << valores[idx_melhor_mochila] << endl;

    /*
      <> obs!!

      Após rodar algumas vezes, os melhores fittings obtidos são:
          - input 1 > 229
              - 1 1 0 0 0 0 0 1 0 0
          - input 2 > 325
              - 0 1 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0
          - input 3 >
              - muito grande... kkk

          ... basta rodar mais vezes para obter resultados diferentes e possivelmente melhores
  */

    //$ MOCHILA CHEIA :D
    // -> pega a melhor mochila. Analisa os itens q não foram incluídos. Se couberem, adiciona na mochila

    vector<int> melhor_mochila = mochilas_geradas[idx_melhor_mochila];

    double peso_melhor_mochila = 0;
    for (int i = 0; i < n_total; i++) {
        if (melhor_mochila[i] == 1) {
            peso_melhor_mochila += itens[i].peso;
        }
    }

    for (int i = 0; i < n_total; i++) {
        if (melhor_mochila[i] == 0) {
            if (peso_melhor_mochila + itens[i].peso <= capacidade) {
                peso_melhor_mochila += itens[i].peso;
                melhor_mochila[i] = 1;
            }
        }
    }

    cout << "Mochila cheia: " << endl;
    for (int i = 0; i < n_total; i++) {
        cout << melhor_mochila[i] << " ";
    }

    double valor_total = calculate_fitting(itens, melhor_mochila);
    cout << "Valor total: " << valor_total << endl;

    return 0;

    // <> COMENTÁRIO

    /*
        Para a in1.txt, a estratégia de Aleatorização + Inclusão de itens que cabem na mochila não teve melhora significativa.
        Porém, quando a capacidade da mochila aumenta, a estratégia passa a demonstrar um resultado mais significativo. (426 -> 503)


        * OBS.:
            * - Aqui, a estratégia utilizada foi adicionar o primeiro item que couber, seguindo a ordem de leitura do arquivo.
            * - Poderíamos utilizar outras estratégias: Adicionar o primeiro mais valioso, adicionar o primeiro mais leve, etc.
            * - Poderíamos também utilizar uma estratégia parecida com a da busca-local: adicionar todas as combinações possíveis de
            * itens extras e escolher a melhor combinação.
    */
}