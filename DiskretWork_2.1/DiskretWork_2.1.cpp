#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct edge // ����� �����
{
    int x, y, w; // x, y - ������ ������, w - ��� �����.
    edge(){}
    edge(int x, int y, int w) : x(x), y(y), w(w){}
};

bool comp(const edge& a, const edge& b);
int getFather(int x);
bool Unite(int x, int y);

vector <int> Father; // ������ "�����"

int main()
{
    setlocale(LC_ALL, ".1251");
    int original_sum = 0;
    int n, m; // ���������� ������ � ����
    cout << "������� ���������� ������: ";
    cin >> n;
    cout << "������� ���������� ����: ";
    cin >> m;

    vector <edge> e(m); // ������ ����

    cout << endl;
    cout << "(��������� ������ ���������� � 1)" << endl;
    cout << "������ ������ ������ ������ � ��� ����������\n"
         <<"� ������� (�1 \'������\' �2 \'������\' ��� ���������� 'Enter')" << endl;
    for (int i = 0; i < m; i++)
    {
        cin >> e[i].x >> e[i].y >> e[i].w;
        e[i].x--;
        e[i].y--;
    }

    sort(e.begin(), e.end(), comp); // ��������� � ������� ���������� ������ ����

    for (int i = 0; i < e.size(); i++) // ������� ��� ��������� �����
        original_sum += e[i].w;

    Father.resize(n); // ��������� ������ ��� ������� "�����"

    for (int i = 0; i < n; i++) // ��������� ������ "�����" �������� ������
        Father[i] = i;

    vector <edge> T; // ������� '������' - �����

    for (int i = 0; i < m; i++)
    {
        int x = e[i].x, y = e[i].y;

        if (Unite(x, y))        // ���� ������� �����������,
            T.push_back(e[i]);  // �� ��������� ����� � ��� ����� (������)
    }

    int final_sum = 0;
    for (int i = 0; i < T.size(); i++) // ������� ��� ����������� ������
        final_sum += T[i].w;

    cout << endl;
    cout << "��� ������������ ����� = " << original_sum << endl;
    cout << "��� ������ = " << final_sum << endl;
    cout << endl;
    cout << "������ ��������������� ������ � ������ �����:" << endl;
    for (int i = 0; i < T.size(); i++)
        cout << T[i].x + 1 << "\t" << T[i].y + 1 << endl;

    return 0;
}

bool comp(const edge& a, const edge& b)
{ // ����� ������� �������, �� �������� �� ���������� ����
    return a.w < b.w;
}

int getFather(int x)
{ // ����� �� ������ �����
    if (x == Father[x])
        return x;

    return Father[x] = getFather(Father[x]);
}

bool Unite(int x, int y)
{ // ����������
    x = getFather(x);
    y = getFather(y);

    if (x == y) // ���� "����" ����� (��������� ����)
        return false;

    if (rand() % 2 == 0)
        swap(x, y);

    Father[x] = y;
    return true;
}
