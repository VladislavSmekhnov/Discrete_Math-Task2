#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge // ребро графа
{
    int x, y, w; // x, y - номера вершин, w - вес ребра.
    edge(){}
    edge(int x, int y, int w) : x(x), y(y), w(w){}
};

bool comp(const edge& a, const edge& b);
int getFather(int x);
bool Unite(int x, int y);

vector <int> Father; // массив "отцов"

int main()
{
    setlocale(LC_ALL, ".1251");
    int original_sum = 0;
    int n, m; // количество вершин и рёбер
    cout << "Введите количество вершин: ";
    cin >> n;
    cout << "Введите количество рёбер: ";
    cin >> m;

    vector <edge> e(m); // храним рёбра

    cout << endl;
    cout << "(Нумерация вершин начинается с 1)" << endl;
    cout << "Теперь укажем номера вершин и вес соединения\n"
         <<"в формате (№1 \'пробел\' №2 \'пробел\' вес соединения 'Enter')" << endl;
    for (int i = 0; i < m; i++)
    {
        cin >> e[i].x >> e[i].y >> e[i].w;
        e[i].x--;
        e[i].y--;
    }

    sort(e.begin(), e.end(), comp); // сортируем в порядке неубывания массив рёбер

    for (int i = 0; i < e.size(); i++) // считаем вес исходного графа
        original_sum += e[i].w;

    Father.resize(n); // назначаем размер для массива "отцов"

    for (int i = 0; i < n; i++) // заполняем массив "отцов" номерами вершин
        Father[i] = i;

    vector <edge> T; // искомое 'дерево' - остов

    for (int i = 0; i < m; i++)
    {
        int x = e[i].x, y = e[i].y;

        if (Unite(x, y))        // если условие выполняется,
            T.push_back(e[i]);  // то добавляем ребро в наш остов (дерево)
    }

    int final_sum = 0;
    for (int i = 0; i < T.size(); i++) // считаем вес полученного остова
        final_sum += T[i].w;

    cout << endl;
    cout << "Вес изначального графа = " << original_sum << endl;
    cout << "Вес остова = " << final_sum << endl;
    cout << endl;
    cout << "Номера задействованных вершин в остове графа:" << endl;
    for (int i = 0; i < T.size(); i++)
        cout << T[i].x + 1 << "\t" << T[i].y + 1 << endl;

    return 0;
}

bool comp(const edge& a, const edge& b)
{ // здесь описано правило, по которому мы сравниваем рёбра
    return a.w < b.w;
}

int getFather(int x)
{ // здесь мы узнаем номер
    if (x == Father[x])
        return x;

    return Father[x] = getFather(Father[x]);
}

bool Unite(int x, int y)
{ // объединяем
    x = getFather(x);
    y = getFather(y);

    if (x == y) // если "отец" общий (совпадают отцы)
        return false;

    if (rand() % 2 == 0)
        swap(x, y);

    Father[x] = y;
    return true;
}
