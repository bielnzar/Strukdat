#include <iostream>
#include <cstdlib>

using namespace std;

typedef struct queueNode_t
{
  int data;
  int pos;
  struct queueNode_t *next;
} QueueNode;

typedef struct queue_t
{
  QueueNode *_front, *_rear;
  unsigned _size;
} Queue;

bool queue_isEmpty(Queue *queue)
{
  return (queue->_front == NULL && queue->_rear == NULL);
}

int queue_front(Queue *queue)
{
  if (!queue_isEmpty(queue))
  {
    return (queue->_front->data);
  }
  return 0;
}

int queue_front_pos(Queue *queue)
{
  if (!queue_isEmpty(queue))
  {
    return (queue->_front->pos);
  }
  return 0;
}

void queue_push(Queue *queue, int value, int pos)
{
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
  if (newNode)
  {
    queue->_size++;
    newNode->data = value;
    newNode->pos = pos;
    newNode->next = NULL;

    if (queue_isEmpty(queue))
    {
      queue->_front = queue->_rear = newNode;
    }
    else
    {
      queue->_rear->next = newNode;
      queue->_rear = newNode;
    }
  }
}

void queue_pop(Queue *queue)
{
  if (!queue_isEmpty(queue))
  {
    QueueNode *temp = queue->_front;
    queue->_front = queue->_front->next;
    free(temp);

    if (queue->_front == NULL)
      queue->_rear = NULL;
    queue->_size--;
  }
}

int main()
{
  Queue ticket;
  ticket._front = ticket._rear = NULL;
  ticket._size = 0;

  int n;
  cin >> n;

  int s = 0;
  int ticketValue;

  for (int i = 0; i < n; i++)
  {
    cin >> ticketValue;
    queue_push(&ticket, ticketValue, i);
  }

  int k;
  cin >> k;

  while (!queue_isEmpty(&ticket))
  {
    int queueVal = queue_front(&ticket) - 1;
    int queuePos = queue_front_pos(&ticket);

    if (queueVal == 0)
    {
      queue_pop(&ticket);
    }
    else
    {
      queue_pop(&ticket);
      queue_push(&ticket, queueVal, queuePos);
    }

    s++;

    if (queuePos == k && queueVal == 0)
    {
      break;
    }
  }

  cout << s << endl;

  return 0;
}
