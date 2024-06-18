// not tested

#include "btree.h"
#include "pila.h"
#include <assert.h>
#include <stdlib.h>

// Queue implementation
typedef struct _QueueNode {
  BTree data;
  struct _QueueNode *next;
} QueueNode;

typedef struct {
  QueueNode *front;
  QueueNode *rear;
} Queue;

Queue *createQueue() {
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  queue->front = queue->rear = NULL;
  return queue;
}

void enqueue(Queue *queue, BTree data) {
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
  newNode->data = data;
  newNode->next = NULL;

  if (queue->rear == NULL) {
    queue->front = queue->rear = newNode;
  } else {
    queue->rear->next = newNode;
    queue->rear = newNode;
  }
}

BTree dequeue(Queue *queue) {
  if (queue->front == NULL) {
    return NULL;
  }

  QueueNode *temp = queue->front;
  BTree data = temp->data;
  queue->front = queue->front->next;

  if (queue->front == NULL) {
    queue->rear = NULL;
  }

  free(temp);
  return data;
}

void btree_recorrer_bfs(BTree arbol, FuncionVisitanteInt visit, int n) {
  Queue *queue = createQueue();

  if (arbol != NULL) {
    enqueue(queue, arbol);
  } else {
    return;
  }

  int depth = 0;

  while (queue->front != NULL) {
    int nodesAtCurrentLevel = queue->rear - queue->front + 1;
    int level = 0;

    while (level < nodesAtCurrentLevel) {
      BTree current = dequeue(queue);

      if (depth == n) {
        visit(current->dato);
      }

      if (current->left != NULL) {
        enqueue(queue, current->left);
      }

      if (current->right != NULL) {
        enqueue(queue, current->right);
      }

      level++;
    }

    depth++;

    if (depth > n) {
      break;
    }
  }

  // Free memory
  while (queue->front != NULL) {
    dequeue(queue);
  }
  free(queue);
}


void btree_recorrer_bfs(BTree arbol, FuncionVisitanteInt visit, int n) {
  Queue *queue = createQueue();

  if (arbol != NULL) {
    enqueue(queue, arbol);
  } else {
    return;
  }

  int depth = 0;

  while (queue->front != NULL) {
    int nodesAtCurrentLevel = queue->rear - queue->front + 1;
    int level = 0;

    while (level < nodesAtCurrentLevel) {
      BTree current = dequeue(queue);

      if (depth == n) {
        visit(current->dato);
      }

      if (current->left != NULL) {
        enqueue(queue, current->left);
      }

      if (current->right != NULL) {
        enqueue(queue, current->right);
      }

      level++;
    }

    depth++;

    
  }

  // Free memory
  while (queue->front != NULL) {
    dequeue(queue);
  }
  free(queue);
}