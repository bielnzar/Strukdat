#include <iostream>
#define MAX_CHAR 26
#define MAX_SIZE 1000

char queueData[MAX_SIZE];
int frontIdx = -1;
int rearIdx = -1;

namespace custom_queue {
    // Fungsi untuk memeriksa apakah antrian kosong
    bool isEmpty() {
        return frontIdx == -1;
    }

    // Fungsi untuk memeriksa apakah antrian penuh
    bool isFull() {
        return (rearIdx + 1) % MAX_SIZE == frontIdx;
    }

    // Fungsi untuk menambahkan elemen ke antrian
    void push(char value) {
        if (isFull()) {
            std::cerr << "Queue overflow\n";
            return;
        }
        if (frontIdx == -1)
            frontIdx = 0;
        rearIdx = (rearIdx + 1) % MAX_SIZE;
        queueData[rearIdx] = value;
    }

    // Fungsi untuk menghapus elemen dari antrian
    void pop() {
        if (isEmpty()) {
            std::cerr << "Queue underflow\n";
            return;
        }
        if (frontIdx == rearIdx)
            frontIdx = rearIdx = -1;
        else
            frontIdx = (frontIdx + 1) % MAX_SIZE;
    }

    // Fungsi untuk mendapatkan elemen pertama dari antrian
    char front() {
        if (isEmpty()) {
            std::cerr << "Queue is empty\n";
            return '\0';
        }
        return queueData[frontIdx];
    }
}

// Insert dan update character count
void insertAndUpdate(int charCount[], char ch) {
    using namespace custom_queue;
    if (ch != ' ') {
        ++charCount[ch - 'a'];
        push(ch);
    }

    // Memeriksa dan menghapus karakter yang muncul lebih dari sekali dari antrian
    while (!isEmpty()) {
        if (charCount[front() - 'a'] > 1)
            pop();
        else
            break;
    }
}

// Cari karakter pertama yang tidak berulang
char getFirstNonRepeating(int charCount[]) {
    using namespace custom_queue;
    if (isEmpty())
        return '#';
    return front();
}

int main() {
    using namespace std;

    // Input string
    string input;
    getline(cin, input);

    // Array untuk menyimpan jumlah kemunculan karakter
    int charCount[MAX_CHAR] = {0};

    // Memproses setiap karakter dalam input
    for (char ch : input) {
        // Memasukkan karakter ke dalam antrian dan memperbarui jumlah kemunculannya
        insertAndUpdate(charCount, ch);
        // Mencetak karakter pertama yang tidak berulang
        if (ch != ' ')
            cout << getFirstNonRepeating(charCount);
    }

    return 0;
}
