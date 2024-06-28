//Soal 2
/*SYL Rental*/

#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

/* Struktur Node */

typedef struct pqueueNode_t {
    int data;
    int prior;
    struct pqueueNode_t *next;
    int id;
} PQueueNode;

/* Struktur ADT PriorityQueue menggunakan Linked List */

typedef struct pqueue_t {
    PQueueNode *_top;
    unsigned _size;
} PriorityQueue;

/* Function prototype */

void pqueue_init(PriorityQueue *pqueue);
bool pqueue_isEmpty(PriorityQueue *pqueue);
void pqueue_push(PriorityQueue *pqueue, int value, int priorval, int id);
void pqueue_pop(PriorityQueue *pqueue);
int  pqueue_top(PriorityQueue *pqueue);

/* Function definition below */

void pqueue_init(PriorityQueue *pqueue)
{
    pqueue->_top = NULL;
    pqueue->_size = 0;
}

bool pqueue_isEmpty(PriorityQueue *pqueue) {
    return (pqueue->_top == NULL);
}

void pqueue_push(PriorityQueue *pqueue, int value, int priorval, int ids)
{
    PQueueNode *temp = pqueue->_top;
    PQueueNode *newNode = new PQueueNode;
    newNode->data = value;
    newNode->prior = priorval;
    newNode->id = ids;
    newNode->next = NULL;

    if (pqueue_isEmpty(pqueue)) {
        pqueue->_top = newNode;
        pqueue->_size+=1;
        return;
    }

    if (priorval > pqueue->_top->prior){
        newNode->next = pqueue->_top;
        pqueue->_top = newNode; 
    }
    else if (priorval == pqueue->_top->prior && value > temp->data){
        newNode->next = pqueue->_top;
        pqueue->_top = newNode;    
    }   
    else {
        while (temp->next != NULL && temp->next->prior == priorval){
            if (value < temp->next->data){
                temp = temp->next;
            }
            else {
                break;
            }
        }
        while ( temp->next != NULL && temp->next->prior > priorval){
            temp = temp->next;
        }
        
        while (temp->next != NULL && temp->next->prior == priorval){
            if (value < temp->next->data){
                temp = temp->next;
            }
            else {
                break;
            }
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }

    pqueue->_size+=1;
}

void pqueue_pop(PriorityQueue *pqueue)
{
    if (!pqueue_isEmpty(pqueue)) {
        PQueueNode *temp = pqueue->_top;
        pqueue->_top = pqueue->_top->next;
        delete temp;
        pqueue->_size-=1;
    }
}

int pqueue_top(PriorityQueue *pqueue) {
    if (!pqueue_isEmpty(pqueue))
        return pqueue->_top->id;
    else return 0;
}

int main(int argc, char const *argv[])
{
    // objek PriorityQueue
    PriorityQueue myPque, pQueStore;

    pqueue_init(&myPque);
    pqueue_init(&pQueStore);

    int N;
    cin >> N;
    
    int i;
    int x;
    string command;
    int rating, capacity, id, sewa;
    
    for(i=0; i<N; i++){
        cin >> command;
        if (command == "REGIS"){
            cin >> id >> rating >> capacity;
            pqueue_push(&myPque, capacity, rating, id);
        }
        else if(command == "SEWA"){
            cin >> sewa;
            
            while(!pqueue_isEmpty(&myPque)){
                if (sewa > 0){
                    sewa-=myPque._top->data;
                    pqueue_push(&pQueStore, myPque._top->data, myPque._top->prior, myPque._top->id);
                    pqueue_pop(&myPque);
                }else {
                    break;
                }
            }
            
            if (sewa <= 0){
                while (!pqueue_isEmpty(&pQueStore)){
                    cout << pqueue_top(&pQueStore) << " ";
                    pqueue_pop(&pQueStore);   
                }
                cout << "telah berhasil disewa" << endl;
            } 
            else {
                while (!pqueue_isEmpty(&pQueStore)){
                    pqueue_push(&myPque, pQueStore._top->data, pQueStore._top->prior, pQueStore._top->id);
                    pqueue_pop(&pQueStore);   
                }
                cout << "Maaf tidak ada bus yang dapat memenuhi keinginan anda" << endl;
            }
        }
    }
    
    if (!pqueue_isEmpty(&myPque)){  
        cout << "Ada " << myPque._size << " bus yang tersisa yaitu";
        while (!pqueue_isEmpty(&myPque)) {
            cout << " " << pqueue_top(&myPque);
            pqueue_pop(&myPque);
        }   
    }else {
        cout << "Tidak ada bus yang tersisa";
    }
    
    return 0;
}
