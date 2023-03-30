#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void read_input_distances(int size, vector<vector<int>> &distances) {
    for (int i = 0; i < size; i++) {
        vector<int> row;

        for (int j = 0; j < size; j++) {
            int distance = 0;
            cin >> distance;

            row.push_back(distance);
        }

        distances.push_back(row);
    }
}

void gulosa(int n, vector<vector<int>> &distances) {
}

int find_next_center(vector<vector<int>> &distancias, int ultimo_centro = 0) {
    int idx = max_element(distancias[ultimo_centro].begin(), distancias[ultimo_centro].end()) - distancias[ultimo_centro].begin();

    return idx;
}

void who_i_belong_to(vector<vector<int>> &distances, vector<int> &centros, vector<int> &answers) {
    answers.clear();

    for (uint v = 0; v < distances.size(); v++) {
        int d1 = distances[centros[0]][v];
        int d2 = distances[centros[1]][v];

        // cout << "i= " << v << " d1= " << d1 << " d2= " << d2 << endl;

        if (d1 < d2) {
            answers.push_back(centros[0]);

        } else {
            answers.push_back(centros[1]);
        }
    }

    for (uint i = 0; i < answers.size(); i++) {
        cout << answers[i] << " ";
    }

    cout << endl;
}

int main() {
    int n = 0;
    int k = 0;
    cin >> n;
    cin >> k;

    vector<vector<int>> distances;
    vector<int> centros;
    vector<int> answers;

    // TODO: Refaça para K variável

    read_input_distances(n, distances);

    for (int centro1 = 0; centro1 < n; centro1++) {

        int centro2 = find_next_center(distances, 3);

        cout << centro1 << " " << centro2 << endl;

        centros = {centro1, centro2};

        who_i_belong_to(distances, centros, answers);

        cout << "------" << endl;
    }

    return 0;
}