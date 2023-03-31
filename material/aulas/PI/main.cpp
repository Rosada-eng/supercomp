#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct atividade {
    int id;
    double lat;
    double lon;
};

double distance(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371000;

    double phi1 = lat1 * M_PI / 180;
    double phi2 = lat2 * M_PI / 180;
    double dphi = (lat2 - lat1) * M_PI / 180;
    double dlambda = (lon2 - lon1) * M_PI / 180;
    double a = pow(sin(dphi / 2), 2) + cos(phi1) * cos(phi2) * pow(sin(dlambda / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = R * c;

    return distance;
}

void read_activities_input(vector<atividade> &activities, int n) {
    for (int i = 0; i < n; i++) {
        atividade atv;
        atv.id = i;
        cin >> atv.lat;
        cin >> atv.lon;

        activities.push_back(atv);
    }
}

int get_random_index(int min, int max) {
    // srand (time(NULL)) gera um seed diferente para cada vez que executar o programa
    srand(time(NULL));

    // ! Para garantir reprodutibilidade, altere o seed para um valor FIXO
    unsigned int seed = rand();

    // tornar o engine statico garante que a geração de números aleatórios a cada chamada de função
    static default_random_engine generator(seed);
    static uniform_int_distribution<int> distribution(min, max);
    int random_index = distribution(generator);

    return random_index;
}

void calculate_distance_between_activities(vector<atividade> &activities, vector<vector<double>> &distances) {

    for (uint i = 0; i < activities.size(); i++) {
        for (uint j = 0; j < activities.size(); j++) {
            if (i == j) {
                distances[i][j] = 0;
            }
            if (j > i) {
                double d = distance(activities[i].lat, activities[i].lon, activities[j].lat, activities[j].lon);
                distances[i][j] = d;
            } else {
                distances[i][j] = distances[j][i];
            }
        }
    }
}

bool have_i_visited(vector<int> &visited_activities, int idx) {
    return find(visited_activities.begin(), visited_activities.end(), idx) != visited_activities.end();
}

void visit_activity(vector<int> &visited_activities, int idx) {
    visited_activities.push_back(idx);
}

int search_next_activity(vector<vector<double>> &distances, vector<int> &visited_activities, int current_atv_idx) {
    vector<double> distances_to_current_atv = distances[current_atv_idx];

    vector<int> proximity_order;
    for (uint i = 0; i < distances.size(); i++) {
        proximity_order.push_back(i);
    }

    sort(proximity_order.begin(), proximity_order.end(), [&](int i, int j) { return distances_to_current_atv[i] < distances_to_current_atv[j]; });

    // checar se o mais próximo seguinte ainda não foi visitado.
    // o mais próximo sempre será a própria cidade (que deve constar no array `visited_activities`. Portanto, não precisamos tratar esse caso)

    int next_in_order = 0;
    int next_atv_to_visit_idx = proximity_order[next_in_order];
    bool already_visited = have_i_visited(visited_activities, next_atv_to_visit_idx);

    while (already_visited) {
        next_in_order += 1;
        next_atv_to_visit_idx = proximity_order[next_in_order];
        already_visited = have_i_visited(visited_activities, next_atv_to_visit_idx);
    }

    return next_atv_to_visit_idx;
}

int main() {
    int n = 0;
    cin >> n;

    int k = n; //! HARDCODED -> k é uma variável adicional para indicar uma limitação de atividades

    vector<atividade> activities;
    activities.reserve(n);

    read_activities_input(activities, n);

    vector<vector<double>> distances;

    vector<double> dist_linha;
    for (int i = 0; i < n; i++) {
        dist_linha.push_back(-1.0);
    }

    for (int i = 0; i < n; i++) {
        distances.push_back(dist_linha);
    }

    calculate_distance_between_activities(activities, distances);

    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << distances[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // TODO: Para limitar orçamento, podemos supor que cada atividade tem o mesmo custo e que os viajantes só têm orçamento para K atividades
    // problems -> K precisaria estar no input do txt (ou podemos fixar ou rodar para alguns valores de K)

    vector<int> visited_activities;

    int first_atv_idx = get_random_index(0, n - 1);
    visit_activity(visited_activities, first_atv_idx);

    while (visited_activities.size() < uint(n)) {

        int next_atv_idx = search_next_activity(distances, visited_activities, visited_activities[visited_activities.size() - 1]);

        visit_activity(visited_activities, next_atv_idx);
    }

    double total_distance = 0;

    for (int i = 0; i < n - 1; i++) {
        if (i + 1 <= k) {
            int origin_idx = visited_activities[i];
            int destiny_idx = visited_activities[i + 1];

            // cout << distances[origin_idx][destiny_idx] << endl;
            total_distance += distances[origin_idx][destiny_idx];
        }
    }

    cout << "Distância total percorrida: ";
    cout << total_distance << " metros" << endl;

    cout << "Ordem das atividades:" << endl;

    int atv_count = 0;
    for (int atv_idx : visited_activities) {
        atv_count += 1;
        if (atv_count <= k) {
            if (atv_idx == visited_activities[visited_activities.size() - 1]) {
                cout << atv_idx + 1 << endl;
            } else {
                cout << atv_idx + 1 << " -> ";
            }
        }
    }

    return 0;
}