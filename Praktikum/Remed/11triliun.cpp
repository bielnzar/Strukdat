#include <bits/stdc++.h>

/*
Nama : Nabiel Nizar Anwari
NRP  : 5027231087
Code : 11 Triliun lagi
*/

using namespace std;

int main() {
    queue <pair <int, int>> q;

    int jumlah;
    cin >> jumlah;
    for (int i = 0; i < jumlah; i++) {
        int bansos;

        cin >> bansos;
        q.push({i, bansos});
    }

    int posisi, waktu = 0;
    cin >> posisi;

    while (!q.empty()) {

        pair <int, int> orang = q.front();
        q.pop();
        waktu++;
        orang.second--;

        if(orang.second > 0) {
            q.push(orang);
        }
        else if (orang.first == posisi && orang.second == 0) {
            break;
        }
    }

    cout << waktu << endl;
}