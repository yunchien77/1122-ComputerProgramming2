/*
032 Double Link List(雙向鏈結串列)

本題必須使用Double Link List實作，否則不予計分。

Double Link List結構:
typedef struct dnode_s {
int data;
struct dnode_s * front;
struct dnode_s * back;
} node_t;
typedef node_t * nodep_t;

8種Double Link List操作：
addFront：將資料放入串列前端，不進行輸出。
addBack：將資料放入串列尾端，不進行輸出。
removeFront：將最前端的節點刪除，假如串列是空的則輸出"Double link list is
empty"，其餘情況不進行輸出。 removeBack :
將最尾端端的節點刪除，假如串列是空的則輸出"Double link list is
empty"，其餘情況不進行輸出。
empty：將串列中所有節點刪除，假如串列是空的則輸出"Double link list is
empty"，其餘情況不進行輸出。 insert n :
在第n個節點後插入新的資料，最前端節點為1。假如串列長度小於n則輸出"Invalid
command"，其餘情況不進行輸出。 remove n :
刪除第n個節點，最前端節點為1。假如串列長度小於n則輸出"Invalid
command"，其餘情況不進行輸出。
print：將串列中所有節點資料從前端到尾端依序每行輸出data，假如串列是空的則輸出"Double
ink list is empty"

【輸入說明】
第一行，輸入一整數 N ( 1 <= N <= 20 )，代表有N個操作。
第二行~第2+N行，輸入操作的種類
addFront操作:addFron
data，addFront為字串，data為整數(0<=data<=100)，中間以空白隔開
addBack操做:addBack
data，addBack為字串，data為整數(0<=data<=100)，中間以空白隔開
removeFront操作:removeFront，removeFront為字串
removeBack操作:removeBack，removeBack為字串
empty操作:empty，empty為字串
insert n操作：insert n
data，insert為字串，n為整數(1<=n<=20)，data為整數(0<=data<=100)，中間以空白隔開
remove n操作：remove n，remove為字串，n為整數(1<=n<=20)，中間以空白隔開
print操作：print，print為字串

範例輸入說明:
13 (N為13，代表有13個操作)
addFront 13(在串列前端加入13)
addBack 12(在串列尾端加入12)
addFront 10(在串列前端加入10)
insert 2 20(在第2個節點後加入20)
insert 5 100(在第5個節點後加入100)
remove 2(移除第2個節點)
print(由前端到尾端輸出所有節點)
remove 5(移除第5個節點)
removeBack(刪除最尾端的節點)
removeFront(刪除最前端的節點)
print(由前端到尾端輸出所有節點)
empty(刪除串列所有節點)
empty(刪除串列所有節點)


【輸出說明】
第一行~第N行，根據操作輸出對應的data

範例輸出說明:
Invalid
command(根據輸入的操作1、2、3、4，串列長度為4，由於5超過串列長度，故指令失效)
10(根據輸入的操作6，串列長度為3，第一個節點的data為10)
20(根據輸入的操作6，串列長度為3，第二個節點的data為20)
12(根據輸入的操作6，串列長度為3，第三個節點的data為12)
Invalid command(目前串列長度為3，由於5超過串列長度，故指令失效)
20(根據輸入操作9、10，串列長度為1，第一個節點的data為20)
Double link list is empty (在操作12時，已將Stack中所有節點刪除，故為空)

【測試資料一】
輸入：
12
removeFront
removeBack
empty
empty
print
print
addFront 12
addFront 14
addFront 15
addBack 17
addBack 16
print


輸出：
Double link list is empty
Double link list is empty
Double link list is empty
Double link list is empty
Double link list is empty
Double link list is empty
15
14
12
17
16

【測試資料二】
輸入：
15
addFront 12
addFront 13
addBack 15
addBack 16
addFront 17
addFront 16
removeFront
removeFront
removeBack
removeBack
print
addBack 15
addFront 14
removeFront
print

輸出：
13
12
13
12
15

【測試資料三】
輸入：
11
addFront 12
addFront 13
addFront 14
insert 1 20
print
insert 5 17
insert 2 19
print
remove 2
remove 5
print


輸出：
14
20
13
12
Invalid command
14
20
19
13
12
Invalid command
14
19
13
12

【測試資料四】
輸入：
10
addFront 13
addFront 14
addBack 15
addBack 16
print
empty
addFront 10
print
empty
empty

輸出：
14
13
15
16
10
Double link list is empty

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dnode_s {
  int data;
  struct dnode_s *front;
  struct dnode_s *back;
} node_t;

typedef node_t *nodep_t;

nodep_t head = NULL;
nodep_t tail = NULL;

void addFront(int data) {
  nodep_t newNode = (nodep_t)malloc(sizeof(node_t));
  newNode->data = data;
  newNode->front = NULL;
  newNode->back = head;
  if (head != NULL) {
    head->front = newNode;
  }
  head = newNode;
  if (tail == NULL) {
    tail = newNode;
  }
}

void addBack(int data) {
  nodep_t newNode = (nodep_t)malloc(sizeof(node_t));
  newNode->data = data;
  newNode->back = NULL;
  newNode->front = tail;
  if (tail != NULL) {
    tail->back = newNode;
  }
  tail = newNode;
  if (head == NULL) {
    head = newNode;
  }
}

void removeFront() {
  if (head == NULL) {
    printf("Double link list is empty\n");
    return;
  }
  nodep_t temp = head;
  head = head->back;
  if (head != NULL) {
    head->front = NULL;
  } else {
    tail = NULL;
  }
  free(temp);
}

void removeBack() {
  if (tail == NULL) {
    printf("Double link list is empty\n");
    return;
  }
  nodep_t temp = tail;
  tail = tail->front;
  if (tail != NULL) {
    tail->back = NULL;
  } else {
    head = NULL;
  }
  free(temp);
}

void empty() {
  if (head == NULL) {
    printf("Double link list is empty\n");
    return;
  }
  while (head != NULL) {
    removeFront();
  }
}

void insert(int n, int data) {
  nodep_t current = head;
  int count = 1;
  while (current != NULL && count < n) {
    current = current->back;
    count++;
  }
  if (current == NULL || count != n) {
    printf("Invalid command\n");
    return;
  }
  nodep_t newNode = (nodep_t)malloc(sizeof(node_t));
  newNode->data = data;
  newNode->front = current;
  newNode->back = current->back;
  if (current->back != NULL) {
    current->back->front = newNode;
  }
  current->back = newNode;
  if (newNode->back == NULL) {
    tail = newNode;
  }
}

void removeNode(int n) {
  nodep_t current = head;
  int count = 1;
  while (current != NULL && count < n) {
    current = current->back;
    count++;
  }
  if (current == NULL || count != n) {
    printf("Invalid command\n");
    return;
  }
  if (current->front != NULL) {
    current->front->back = current->back;
  } else {
    head = current->back;
  }
  if (current->back != NULL) {
    current->back->front = current->front;
  } else {
    tail = current->front;
  }
  free(current);
}

void print() {
  if (head == NULL) {
    printf("Double link list is empty\n");
    return;
  }
  nodep_t current = head;
  while (current != NULL) {
    printf("%d\n", current->data);
    current = current->back;
  }
}

int main() {
  int N;
  scanf("%d", &N);
  char command[20];
  for (int i = 0; i < N; i++) {
    scanf("%s", command);
    if (strcmp(command, "addFront") == 0) {
      int data;
      scanf("%d", &data);
      addFront(data);
    } else if (strcmp(command, "addBack") == 0) {
      int data;
      scanf("%d", &data);
      addBack(data);
    } else if (strcmp(command, "removeFront") == 0) {
      removeFront();
    } else if (strcmp(command, "removeBack") == 0) {
      removeBack();
    } else if (strcmp(command, "empty") == 0) {
      empty();
    } else if (strcmp(command, "insert") == 0) {
      int n, data;
      scanf("%d %d", &n, &data);
      insert(n, data);
    } else if (strcmp(command, "remove") == 0) {
      int n;
      scanf("%d", &n);
      removeNode(n);
    } else if (strcmp(command, "print") == 0) {
      print();
    }
  }
  return 0;
}
