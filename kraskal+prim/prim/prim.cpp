#include <iostream>
#include <vector>
#include <queue>
#include <Windows.h>

using namespace std;

const int MAXN = 100; // максимальное количество вершин в графе
const int INF = 1e9; // значение "бесконечность"

vector<pair<int, int>> g[MAXN]; // граф (список смежности)
bool used[MAXN]; // массив, отмечающий посещенные вершины
int dist[MAXN]; // массив расстояний до вершин (весов ребер)
int parent[MAXN]; // массив предков (для восстановления пути)
priority_queue<pair<int, int>> q; // очередь с приоритетом

int n, m; // количество вершин и ребер в графе
int start; // начальная вершина

void prim() {
    for (int i = 1; i <= n; i++) {
        used[i] = false;
        dist[i] = INF;
        parent[i] = -1;
    }

    dist[start] = 0;
    q.push(make_pair(0, start));

    while (!q.empty()) {
        int v = q.top().second;
        q.pop();

        if (used[v]) {
            continue;
        }
        used[v] = true;

        for (size_t i = 0; i < g[v].size(); i++) {
            int to = g[v][i].first;
            int len = g[v][i].second;

            if (!used[to] && len < dist[to]) {
                dist[to] = len;
                parent[to] = v;
                q.push(make_pair(-dist[to], to));
            }
        }
    }
}

void print_result() {
    int sum = 0;
    cout << "Полученные ребра" << endl;
    for (int i = 1; i <= n; i++) {
        if (parent[i] != -1) {
            sum += dist[i];
            cout << parent[i] << " " << i << " " << dist[i] << endl;
        }
    }

    cout << "Вес остова: " << sum << endl;
}

void input_graph() {
    cout << "Введите количество вершин и количество ребер и начальную точку" << endl;
    cout << "Формат: {количество вершин} {количество ребер} {начальная вершина}" << endl;
    cin >> n >> m >> start;

    cout << "Для каждого ребра введите какие вершины оно соединяет и его вес" << endl;
    cout << "Формат: {вершина1} {вершина2} {вес ребра}" << endl;
    for (int i = 1; i <= m; i++) {
        int from, to, len;
        cin >> from >> to >> len;
        g[from].push_back(make_pair(to, len));
        g[to].push_back(make_pair(from, len));
    }
}

int main() {
    SetConsoleOutputCP(1251);
    input_graph();
    prim();
    print_result();

    return 0;
}