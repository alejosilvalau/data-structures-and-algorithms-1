// Queue *queue create() --> que crea una cola.
// int queue is empty(Queue *) --> que determina si una cola esta vacia.
// void queue enqueue(Queue *, void *) --> que agrega un valor a la cola.
// void *queue front(Queue *) --> que devuelve el elemento en primera posicion.
// Queue *queue dequeue(Queue *) --> que quita el elemento en primera posicion.
// void queue destroy(Queue *) --> que destruye una cola.

// void btree_recorrer_bfs(BTree arbol, FuncionVisitanteInt visit, int n) {
//   Queue *queue = createQueue();

//   if (arbol != NULL) {
//     enqueue(queue, arbol);
//   } else {
//     return;
//   }

//   int depth = 0;

//   while (queue->front != NULL) {
//     int nodesAtCurrentLevel = queue->rear - queue->front + 1;
//     int level = 0;

//     while (level < nodesAtCurrentLevel) {
//       BTree current = dequeue(queue);

//       if (depth == n) {
//         visit(current->dato);
//       }

//       if (current->left != NULL) {
//         enqueue(queue, current->left);
//       }

//       if (current->right != NULL) {
//         enqueue(queue, current->right);
//       }

//       level++;
//     }

//     depth++;

//     if (depth > n) {
//       break;
//     }
//   }

typedef void (*VisitorFuncIntPtr)(int *, void *);

void btree_foreach(BTree *root, VisitorFuncIntPtr visitor, void *extra_data) {
  if (arbol != NULL) {
    Queue *cola = queue_create();
    queue_enqueue(cola, root);
    
    int depth = 0;
    
    while (!queue_is_empty(cola)) {
      int nodesAtCurrentLevel = cola->last - cola->first + 1;
      int level = 0;

      while (level < nodesAtCurrentLevel) {
        BTree* current = (BTree*)queue_front(cola);
        cola = queue_dequeue(cola);

        visitor(current->dato, extra_data);

        if (current->left != NULL) {
          queue_enqueue(cola, current->left);
        }
        if (current->right != NULL) {
          queue_enqueue(cola, current->right);
        }

        level++;
      }
      depth++;
    }
  }
}