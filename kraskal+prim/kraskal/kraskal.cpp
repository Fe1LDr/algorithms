#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
#include <Windows.h>

using namespace std;

const int MAXN = 100; // максимальное количество вершин в графе

vector<pair<int, pair<int, int>>> edges; // вектор ребер

int parent[MAXN]; // массив для хранения предков
int n, m;

int find(int x) {
    if (x == parent[x]) return x;
    return parent[x] = find(parent[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);
    if (x != y) parent[x] = y;
}

int kraskal(int n) {
    int cost = 0;
    for (int i = 0; i < n; i++) parent[i] = i;
    sort(edges.begin(), edges.end());
    for (auto edge : edges) {
        int w = edge.first;
        int u = edge.second.first;
        int v = edge.second.second;
        if (find(u) != find(v)) {
            cost += w;
            merge(u, v);
        }
    }
    return cost;
}

void input_graph() {
    cout << "Введите количество вершин и количество ребер" << endl;
    cout << "Формат: {количество вершин} {количество ребер}" << endl;
    cin >> n >> m;
    cout << "Для каждого ребра введите какие вершины оно соединяет и его вес" << endl;
    cout << "Формат: {вершина1} {вершина2} {вес ребра}" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({ w, {u, v} });
    }
}

int main() {
    SetConsoleOutputCP(1251);
    input_graph();
    cout << kraskal(n) << endl;
    return 0;
}
