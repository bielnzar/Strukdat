#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

// Definisi struktur node untuk doubly linked list
typedef struct dnode_t {
    int data;
    struct dnode_t *next, *prev;
} DListNode;

// Definisi struktur deque
typedef struct deque_t {
    DListNode *_head, *_tail;
    unsigned _size;
} Deque;

// Fungsi untuk membuat node baru
DListNode* __dlist_createNode(int value) {
    DListNode *newNode = (DListNode*) malloc(sizeof(DListNode));
    if (!newNode) return NULL;
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Fungsi untuk menginisialisasi deque
void deque_init(Deque *deque) {
    deque->_head = deque->_tail = NULL;
    deque->_size = 0u;
}

// Fungsi untuk menambahkan node baru di bagian depan deque
bool deque_pushFront(Deque *deque, int value) {
    DListNode *newNode = __dlist_createNode(value);
    if (!newNode) return false;

    if (!deque->_head) {
        deque->_head = deque->_tail = newNode;
    } else {
        newNode->next = deque->_head;
        deque->_head->prev = newNode;
        deque->_head = newNode;
    }
    deque->_size++;
    return true;
}

// Fungsi untuk menghapus node di bagian belakang deque
bool deque_popBack(Deque *deque) {
    if (!deque->_head) return false;

    DListNode *temp = deque->_tail;
    if (deque->_head == deque->_tail) {
        deque->_head = deque->_tail = NULL;
    } else {
        deque->_tail = deque->_tail->prev;
        deque->_tail->next = NULL;
    }
    free(temp);
    deque->_size--;
    return true;
}

// Fungsi untuk mendapatkan data di bagian depan deque
int deque_front(Deque *deque) {
    if (!deque->_head) return -1;
    return (deque->_head->data);
}

// Fungsi untuk mendapatkan data di bagian belakang deque
int deque_back(Deque *deque) {
    if (!deque->_tail) return -1;
    return (deque->_tail->data);
}

// Fungsi untuk memeriksa apakah deque kosong
bool deque_isEmpty(Deque *deque) {
    return (deque->_head == NULL && deque->_tail == NULL);
}

// Fungsi utama
int main() {
    int n;
    cin >> n;

    // Inisialisasi deque untuk menyimpan nomor pesanan
    Deque pesananBiasa, pesananUrgen;
    deque_init(&pesananBiasa);
    deque_init(&pesananUrgen);

    int order = 1; // Variabel untuk menyimpan nomor urutan pesanan
    int pesananTerproses = 0; // Variabel untuk menyimpan jumlah pesanan yang sudah diproses

    // Proses setiap pesanan
    for (int i = 0; i < n; ++i) {
        string urgensi, namaPesanan, namaPemesan;
        int jumlahPesanan;
        cin >> urgensi >> namaPesanan >> jumlahPesanan >> namaPemesan;

        // Memeriksa urgensi pesanan
        if (urgensi == "Biasa") {
            // Menambahkan nomor pesanan ke deque pesanan biasa
            deque_pushFront(&pesananBiasa, order);
        } else {
            // Menambahkan nomor pesanan ke deque pesanan urgen
            deque_pushFront(&pesananUrgen, order);
        }

        order++; // Menambah nomor urutan pesanan
    }

    // Mencetak pesanan urgen yang diterima
    cout << "Pesanan urgen yang diterima:";
    while (!deque_isEmpty(&pesananUrgen) && pesananTerproses < 10) {
        cout << " " << deque_back(&pesananUrgen);
        deque_popBack(&pesananUrgen);
        pesananTerproses++;
    }
    cout << endl;

    // Mencetak pesanan biasa yang diterima
    cout << "Pesanan biasa yang diterima:";
    while (!deque_isEmpty(&pesananBiasa) && pesananTerproses < 10) {
        cout << " " << deque_back(&pesananBiasa);
        deque_popBack(&pesananBiasa);
        pesananTerproses++;
    }
    cout << endl;

    // Mencetak pesanan yang dibatalkan (pesanan yang belum diproses dan melebihi urutan proses ke-10)
    cout << "Pesanan yang dibatalkan:";
    while (!deque_isEmpty(&pesananUrgen)) {
        cout << " " << deque_back(&pesananUrgen);
        deque_popBack(&pesananUrgen);
    }
    while (!deque_isEmpty(&pesananBiasa)) {
        cout << " " << deque_back(&pesananBiasa);
        deque_popBack(&pesananBiasa);
    }
    cout << endl;

    return 0;
}
