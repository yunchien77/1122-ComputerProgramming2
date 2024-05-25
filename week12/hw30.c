/*
30 Queue(佇列)
本題必須使用Link List實作，否則不予計分。

使用Link List模擬queue先進先出（FIFO, First In First Out）的運作原理。

Queue結構:
typedef struct node_s {
int data;
struct node_s * next;
}node_t;
typedef node_t * nodep_t;

5種Queue操作：
push：將資料放入佇列的尾端（串列形式），不進行輸出。
pop：將佇列前端資料輸出，並刪除前端節點，假如佇列是空的則輸出"Queue is empty"。
front：將佇列前端資料輸出，假如佇列是空的則輸出"Queue is empty"。
empty：將佇列中所有節點刪除，假如佇列是空的則輸出"Queue is empty"，不進行輸出。
print：將佇列中所有節點資料從前端到尾端依序每行輸出data，假如佇列是空的則輸出"Queue
is empty"。

【輸入說明】
第一行，輸入一整數 N ( 1 <= N <= 20 )，代表有N個操作。
第二行~第2+N行，輸入操作的種類
push操作：push data，push為字串，data為整數(0<=data<=100)，中間以空白隔開
pop操作：pop，pop為字串
front操作：front，front為字串
empty操作：empty，empty為字串
print操作：print，print為字串

範例輸入說明:
13 (N為13，代表有13個操作)
push 2 (在Queue的尾端加入一個data為2的節點)
push 4 (在Queue的尾端加入一個data為4的節點)
front (將Queue前端data輸出)
push 3 (在Queue的尾端加入一個data為3的節點)
push 1 (在Queue的前端加入一個data為1的節點)
front (將Queue前端data輸出)
pop (將Queue前端data輸出，並刪除前端節點)
front (將Queue前端data輸出)
pop (將Queue前端data輸出，並刪除前端節點)
front (將Queue前端data輸出)
empty (將Queue中所有節點刪除)
front (將Queue前端data輸出)
empty (將Queue中所有節點刪除)

【輸出說明】
第一行~第N行，根據操作輸出對應的data

範例輸出說明:
2 (根據輸入的操作1、2，目前前端節點的data為2)
2 (根據輸入的操作1、2、4、5，目前前端節點的data為2)
2 (目前前端節點的data為2，輸出並刪除該節點)
4 (目前前端節點的data為4)
4 (目前前端節點的data為4，輸出並刪除該節點)
3 (目前前端節點的data為3)
Queue is empty (在操作11時，已將Queue中所有節點刪除，故為空)
Queue is empty (在操作11時，已將Queue中所有節點刪除，故為空)

【測試資料一】
輸入：
10
front
empty
front
front
empty
push 12
push 32
pop
front
pop

輸出：
Queue is empty
Queue is empty
Queue is empty
Queue is empty
Queue is empty
12
32
32

【測試資料二】
輸入：
12
push 14
push 15
push 17
push 10
print
pop
front
pop
pop
print
pop
print

輸出：
14
15
17
10
14
15
15
17
10
10
Queue is empty

【測試資料三】
輸入：
10
print
push 22
push 15
push 18
empty
print
push 1
push 14
pop
empty

輸出：
Queue is empty
Queue is empty
1

【測試資料四】
輸入：
10
push 15
push 18
print
push 22
push 27
push 29
push 13
front
pop
front

輸出：
15
18
15
15
18

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
  int data;
  struct node_s *next;
} node_t;

typedef node_t *nodep_t;

nodep_t front = NULL;
nodep_t rear = NULL;

void push(int data) {
  nodep_t newNode = (nodep_t)malloc(sizeof(node_t));
  newNode->data = data;
  newNode->next = NULL;
  if (rear == NULL) {
    front = newNode;
  } else {
    rear->next = newNode;
  }
  rear = newNode;
}

void pop() {
  if (front == NULL) {
    printf("Queue is empty\n");
  } else {
    nodep_t temp = front;
    printf("%d\n", front->data);
    front = front->next;
    if (front == NULL) {
      rear = NULL;
    }
    free(temp);
  }
}

void front_op() {
  if (front == NULL) {
    printf("Queue is empty\n");
  } else {
    printf("%d\n", front->data);
  }
}

void empty() {
  if (front == NULL) {
    printf("Queue is empty\n");
  } else {
    while (front != NULL) {
      nodep_t temp = front;
      front = front->next;
      free(temp);
    }
    rear = NULL;
  }
}

void print() {
  if (front == NULL) {
    printf("Queue is empty\n");
  } else {
    nodep_t current = front;
    while (current != NULL) {
      printf("%d\n", current->data);
      current = current->next;
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  char command[10];
  int value;

  for (int i = 0; i < n; i++) {
    scanf("%s", command);
    if (strcmp(command, "push") == 0) {
      scanf("%d", &value);
      push(value);
    } else if (strcmp(command, "pop") == 0) {
      pop();
    } else if (strcmp(command, "front") == 0) {
      front_op();
    } else if (strcmp(command, "empty") == 0) {
      empty();
    } else if (strcmp(command, "print") == 0) {
      print();
    }
  }

  // Clean up any remaining nodes in the queue
  // empty();
  return 0;
}
