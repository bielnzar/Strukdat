// Soal 1
// Forgotten Middle Child :C

// Version 2: Using two pointers to find middle node

#include <iostream>
using namespace std;

// Struct untuk masing-masing node
typedef struct Node {
    string data_anak; // Data yang akan diinput berupa string data anak
    Node *next; // Pointer ke node selanjutnya
} list_node;

// Struct untuk linked list
typedef struct singly_linked_list {
    list_node *head; // Pointer ke head dari linked list
} list;

// Function untuk push back data yang mau diinput ke linked list
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
}

// Function untuk print linked list
void print_list(list *linked_list) {

    // Inisialisasi pointer slow dan fast untuk mencari middle node dengan metode two pointers
    list_node *slow = linked_list->head;
    list_node *fast = linked_list->head;
    list_node *prev = NULL;

    // Looping untuk mencari middle node
    while (fast != NULL && fast->next != NULL) {
        prev = slow; // Menyimpan node sebelum slow
        slow = slow->next; // Pointer slow hanya bergeser satu kali
        fast = fast->next->next; // Pointer fast bergeser dua kali

        // Jika fast sudah mencapai node terakhir, maka slow sudah berada di middle node
    }

    list_node *temp = linked_list->head; // Membuat pointer temp yang menunjuk ke head dari linked list

    // Looping untuk print linked list
    while (temp != NULL) {
        // Pointer temp akan print semua node kecuali middle node (slow)
        if (temp != slow) {
            cout << temp->data_anak << ", ";
        }
        temp = temp->next; // Pointer temp akan bergeser ke node selanjutnya
    }
    cout << "sudah dijemput";
    cout << endl;
}

int main() {
    string data;
    list linked_list;
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