// Soal 1
// Forgotten Middle Child :C

// Version 1: Dividing size of linked list by 2 to find middle node

#include <iostream>
using namespace std;

// Struct untuk masing-masing node
typedef struct Node {
    string data_anak; // Data yang akan diinput berupa string data anak
    Node *next; // Pointer ke node selanjutnya
} list_node;

// Struct untuk linked list
typedef struct singly_linked_list {
    unsigned size; // Variable untuk mendefinisikan jumlah node dalam linked list
    list_node *head; // Pointer ke head dari linked list
} list;

// Function untuk push back data yang akan diinput ke linked list
void push_back(list *linked_list, string data) {
    list_node *new_node = new list_node; // Membuat node baru
    new_node->data_anak = data; // Mengisi data anak dari node baru dengan data yang diinput
    new_node->next = NULL; // Mengisi pointer next dari node baru dengan NULL karena node baru diletakkan di akhir linked list

    // Jika linked list masih kosong, maka head akan menunjuk ke new_node
    if (linked_list->head == NULL) {
        linked_list->head = new_node;
    } 
    // Jika linked list sudah ada isinya, maka akan menambahkan new_node di akhir linked list
    else {
        list_node *temp = linked_list->head; // Membuat pointer temp yang menunjuk ke head dari linked list untuk mencari node terakhir
        while (temp->next != NULL) { // Looping sampai menemukan node terakhir
            temp = temp->next; // Menggeser temp ke node selanjutnya untuk mencari node terakhir
        }
        temp->next = new_node; // Karena temp sudah menunjuk ke node terakhir, maka node terakhir akan menunjuk ke new_node
    }
    linked_list->size++; // Increment size dari linked list
}

// Function untuk print linked list
void print_list(list *linked_list) {
    list_node *temp = linked_list->head; // Membuat pointer temp yang menunjuk ke head dari linked list

    // Menghitung posisi middle node
    int middle_pos = linked_list->size / 2;

    // Looping untuk print linked list sambil menghindari middle node
    int count = 0; // Inisialisasi count untuk mengetahui posisi node saat loop
    while (temp != NULL) {
        // Jika count belum bukan middle_pos, maka print node
        if (count != middle_pos) {
            cout << temp->data_anak << ", ";
        }
        count++; // Increment count untuk mengetahui posisi node
        temp = temp->next; // Pointer temp akan bergeser ke node selanjutnya
    }
    cout << "sudah dijemput";
    cout << endl;
}

int main() {
    string data;
    list linked_list;
    linked_list.size = 0;
    linked_list.head = NULL;

    do {
        cin >> data;
        if (data != "done") {
            push_back(&linked_list, data);
        }
    } while (data != "done");

    print_list(&linked_list);

    return 0;
}
