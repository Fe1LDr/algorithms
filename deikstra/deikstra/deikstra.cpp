#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <Windows.h>

using namespace std;

const int INF = 1e9; // значение "бесконечность"
vector<pair<int, int>> g[100]; // граф (список смежности)
vector<int> path; // путь
bool used[100]; // массив, отмечающий посещенные вершины
int dist[100]; // массив расстояний до вершин (весов ребер)
int pred[100]; // массив предков (для восстановления пути)

int n, m; // количество вершин и ребер в графе
int start; // начальная вершина

void Dejkstra(int s)
{
    dist[s] = 0;
    for (int iter = 0; iter < n; ++iter)
    {
        int v = -1;
        int distV = INF;
        // выбираем вершину, кратчайшее расстояние до которой еще не найдено
        for (int i = 0; i < n; ++i)
        {
            if (used[i])
            {
                continue;
            }
            if (distV < dist[i])
            {
                continue;
            }
            v = i;
            distV = dist[i];
        }
        // рассматриваем все дуги, исходящие из найденной вершины
        for (size_t i = 0; i < g[v].size(); i++) {
            int to = g[v][i].first;
            int len = g[v][i].second;
            // релаксация вершины
            if (dist[v] + len < dist[to])
            {
                dist[to] = dist[v] + len;
                pred[to] = v;
            }
        }
        // помечаем вершину v просмотренной, до нее найдено кратчайшее расстояние
        used[v] = true;
    }
}

void ReadData()
{
    cout << "Введите количество вершин и количество ребер и нач точку" << endl;
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

    for (int i = 1; i <= n; i++) {
        used[i] = false;
        dist[i] = INF;
        pred[i] = -1;
    }
}
    
void PrintResult()
{
    for (int i = 1; i < n + 1; ++i)
    {
        if (dist[i] == INF)
        {
            cout << "До вершины " << (i) << " расстояние равно INF" << endl;;
        }
        else
        {
            cout << "До вершины " << (i) << " расстояние равно " << dist[i] << endl;;
        }

        int cur = i;
        while (cur != start) {
            path.push_back(cur);
            cur = pred[cur];
        }

        path.push_back(start);
        cout << "Путь: ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i != path.size() - 1) {
                cout << "->";
            }
        }
        path.clear();
        cout << '\n';
    }

}
    
int main() {
    SetConsoleOutputCP(1251);
    ReadData();
    Dejkstra(start);
    PrintResult();
    return 0;
}