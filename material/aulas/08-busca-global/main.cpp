#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/*
    PSEUDOCÓDIGO

    - iniciando com o item[0]:
        - [] Inclue ele na mochila:
            -> Resolve o problema para mochila(N-1 itens, V-p espaços)
            return S1

        - [] Não inclue ele na mochila:
            -> Resolve o problema para mochila(N-1 itens, V espaços)
            return S2

        compara S1 e S2 e retorna o melhor


*/

struct item {
    int id;
    double peso;
    double valor;
};

void read_input_items(vector<item> &destiny, int n_total) {
    double w;
    double v;
    for (int i = 0; i < n_total; i++) {
        cin >> w;
        cin >> v;
        destiny.push_back({i, w, v});
    }
}

double calcula_peso(vector<item> &itens) {
    double peso = 0.0;
    for (auto &el : itens) {
        peso += el.peso;
    }
    return peso;
}

double calcula_valor(vector<item> &itens) {
    double valor = 0.0;
    for (auto &el : itens) {
        valor += el.valor;
    }
    return valor;
}

double resolve_mochila(double W, vector<item> itens, vector<item> &usados, vector<item> &melhor) {
    // W -> capacidade da mochila atual
    // items -> itens disponíveis para a mochila atual
    // deve ser uma cópia do array original, pois sofrerá alterações que não devem interferir no processo seguinte

    // usados -> itens selecionados até agora
    // melhor -> melhor solução encontrada até agora

    double S1 = 0.0;
    double S2 = 0.0;

    // caso base
    if (itens.empty() || W == 0) {
        return 0.0;
    }
    // TODO:
    //! AINDA PODEMOS OTIMIZAR NOSSO CÓDIGO
    // em alguns momentos, nossa mochila já está cheia. Então, não é necessário aprofundar nos ramos. Podemos chamar return logo.

    double valor_atual = calcula_valor(usados);
    double peso_atual = calcula_peso(usados);

    if (peso_atual == W) {
        return 0.0;
        // Não precisa aprofundar os nós da árvore, pois nenhum item a mais será inserido.

        // obs.: Isso já estava refletido no if anterior ( W == 0)
    }

    // sabemos todos os elementos possíveis ramo abaixo (items). Logo, podemos estimar quanto a mais de valor pode ser obtido se percorressemos todo o ramo.

    double valor_possivel = calcula_valor(itens);
    double valor_melhor = calcula_valor(melhor);

    if (valor_atual + 1 * valor_possivel < valor_melhor) {
        return 0.0;

        // se o valor possível de obter não superar o melhor_valor já calculado, não há por que percorrer o ramo!
    }

    //<> dúvida: -- Por que duplicar items?
    //<> dúvida: -- O que é o num_copy que o professor contou?
    // -> num_copy é o número de vezes que copiamos o array de usados para o array `melhor`.
    // -> seria um máximo_local ??

    // pega o primeiro item
    item primeiro = itens[0];

    // remove o primeiro item
    itens.erase(itens.begin());

    // ramifica
    vector<item> itens2 = itens;

    // inclui o primeiro item
    if (primeiro.peso <= W) {
        usados.push_back(primeiro);
        S1 = primeiro.valor + resolve_mochila(W - primeiro.peso, itens, usados, melhor);
    }

    // não inclui o primeiro item
    S2 = resolve_mochila(W, itens2, usados, melhor);

    valor_atual = 0.0;
    valor_melhor = 0.0;

    // "usados" é um array que registra cada um dos itens consumidos da raiz até a folha.
    // o cálculo do peso e valor deve ser feito quando chegarmos na última chamda recursiva (folha)
    // nesse instante, todos os itens consumidos estão registrados no array `usados`
    // basta calcular o valor obtido e comparar com o melhor valor encontrado até agora
    // se for melhor, atualiza o array `melhor` com os nós/itens selecionados até então

    cout << "Ramo: "
         << " ";
    for (auto &el : usados) {
        cout << el.id << " ";
        valor_atual += el.valor;
    }
    cout << endl;

    for (auto &el : melhor) {
        valor_melhor += el.valor;
    }

    if (valor_atual > valor_melhor) {
        melhor = usados;
    }

    // mas, como o array `usados` é passado por referência, ele é compartilhado com os outros ramos (S2) e, portanto, seu resultado deve ser limpo antes de analisarmos o ramo anterior.

    // portanto, antes do return, devemos chamar `usados.clear()`
    usados.clear();
    return max(S1, S2);
}

int main() {

    int n_total;
    double W;

    cin >> n_total;
    cin >> W;

    vector<item> itens;
    itens.reserve(n_total);

    read_input_items(itens, n_total);

    vector<item> usados;
    usados.reserve(n_total);

    vector<item> melhor;

    double valor = resolve_mochila(W, itens, usados, melhor);

    cout << "Valor obtido: " << valor << endl;

    // obs.: A mochila obtida contém a ordem inversa de elementos inseridos. Basta invertê-la.
    reverse(usados.begin(), usados.end());

    cout << "Melhor ramo: ";
    for (auto &item : melhor) {
        cout << item.id << " ";
    }

    return 0;
}