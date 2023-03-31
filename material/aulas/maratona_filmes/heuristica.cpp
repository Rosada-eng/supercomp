#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

bool DEBUG = false; // VARIABLE TO PRINT DEBUG MESSAGES

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

        if (m.end < m.start) {
            m.end += 24; // acaba no dia seguinte
        }

        int category = 0;
        cin >> category;

        m.category = category - 1;

        // HARD FIX -> Alinha categoria com o índice dos arrays

        book.push_back(m);
    }
}

void sort_book_by_ending_time(vector<movie> &book, vector<int> &sorting_list) {
    sort(sorting_list.begin(), sorting_list.end(), [&](int i, int j) { return book[i].end < book[j].end; });
}

void book_a_movie(vector<movie> &book, vector<int> &movies_booked, vector<int> &categories_booked, int movie_id) {
    movies_booked.push_back(movie_id);
    categories_booked.push_back(book[movie_id].category);
}

int main() {
    vector<movie> book;
    int n = 0;
    int k = 0;

    cin >> n;
    cin >> k;

    vector<int> categories_max_size;
    categories_max_size.reserve(k);

    for (int i = 0; i < k; i++) {
        int max_size = 0;
        cin >> max_size;
        categories_max_size.push_back(max_size);
    }

    cout << "max_by_category: ";
    for (int i = 0; i < k; i++) {
        cout << categories_max_size[i] << " ";
    }

    cout << endl;

    vector<int> movies_booked;
    vector<int> categories_booked;

    read_movies_booking(n, book);

    // utilizaremos ordenação indireta
    vector<int> sorting_movies;
    sorting_movies.reserve(n);

    for (int i = 0; i < n; i++) {
        sorting_movies.push_back(i);
    }

    sort_book_by_ending_time(book, sorting_movies);

    vector<int> booked_backup;
    int last_seen_finishes_at = 0;
    for (int day = 0; day < 2; day++) {
        for (int i = 0; i < n; i++) {
            int movie_id = sorting_movies[i];
            int category = book[movie_id].category;

            // checa se o filme já não foi assistido
            bool movie_is_taken = find(movies_booked.begin(), movies_booked.end(), movie_id) != movies_booked.end();

            // checa se estourou limite para categoria
            bool category_limit_exceeded = count(categories_booked.begin(), categories_booked.end(), category) >= categories_max_size[category];

            // checa se o filme anterior já acabou no horário de início do filme atual
            bool is_time_available = (movies_booked.size() == 0) || (book[movie_id].start >= last_seen_finishes_at);

            if (DEBUG) {
                cout << "M" << movie_id << "\t" << book[movie_id].start << "~" << book[movie_id].end << " C" << book[movie_id].category;
            }

            // se passar nos dois filtros, adiciona o filme
            if (!category_limit_exceeded && !movie_is_taken && is_time_available) {
                if (DEBUG) {
                    cout << "\t is available";
                }
                book_a_movie(book, movies_booked, categories_booked, movie_id);

                last_seen_finishes_at = book[movie_id].end;
            }

            if (DEBUG) {
                if (!is_time_available) {
                    cout << "\t time is not available "
                         << "(" << book[movies_booked.back()].end << ")";
                }
                if (category_limit_exceeded) {
                    cout << "\t category limit exceeded";
                }
                if (movie_is_taken) {
                    cout << "\t movie is taken";
                }
                cout << endl;
            }
        }

        if (last_seen_finishes_at >= 24) {
            last_seen_finishes_at -= 24;
        }
    }

    for (uint i = 0; i < movies_booked.size(); i++) {
        cout << movies_booked[i] << " ";
    }

    cout << endl
         << "total: " << movies_booked.size() << endl;

    // TODO: implementar um mapa com os horários alocados para filmes

    cout << endl;
    return 0;
}