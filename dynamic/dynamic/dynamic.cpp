#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <Windows.h>

using namespace std;

const int INF = 1e9; // значение "бесконечность"
vector<pair<int, pair<int, int>>> g; // граф (список смежности)
vector<int> path; // путь
int dist[100]; // массив расстояний до вершин (весов ребер)
int pred[100]; // массив предков (для восстановления пути)

int n, m; // количество вершин и ребер в графе
int start; // начальная вершина

void ReadData()
{
    cout << "Введите количество вершин и количество ребер и нач точку" << endl;
    cout << "Формат: {количество вершин} {количество ребер} {начальная вершина}" << endl;
    cin >> n >> m >> start;

    cout << "Для каждого ребра введите какие вершины оно соединяет и его вес" << endl;
    cout << "Формат: {вершина1} {вершина2} {вес ребра}" << endl;
    for (int i = 1; i <= m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.push_back({ w, {u, v} });
    }

    for (int i = 1; i <= n; i++) {
        dist[i] = INF;
        pred[i] = -1;
    }
}

void dynamic(int s)
{
    dist[s] = 0;

    for (int iter = 0; iter <= n; iter++)
    {
        for (auto edge : g)
        {
            int u = edge.second.first;
            int v = edge.second.second;
            int w = edge.first;
            if (dist[u] != INF && dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pred[v] = u;
            }
        }
    }
    for (auto edge : g)
    {
        int u = edge.second.first;
        int v = edge.second.second;
        int w = edge.first;
        if (dist[u] != INF && dist[u] + w < dist[v])
        {
            cout << "- цикл" << endl;
            return;
        }
    }
}

void PrintResult()
{
    for (int i = 1; i < n + 1; ++i)
    {
        if (dist[i] == INF)
        {
            cout << "До вершины " << (i) << " расстояние равно INF" << endl;
        }
        else
        {
            cout << "До вершины " << (i) << " расстояние равно " << dist[i] << endl;
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



int main()
{
    SetConsoleOutputCP(1251);
    ReadData();
    dynamic(start);
    PrintResult();
}

