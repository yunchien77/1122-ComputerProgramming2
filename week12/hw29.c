/*
029 Stack(堆疊)
本題必須使用Link List實作，否則不予計分。

使用Link List模擬stack後進先出（LIFO, Last In First Out）的運作原理。

Stack結構:
typedef struct node_s {
int data;
struct node_s * next;
}node_t;
typedef node_t * nodep_t;

5種Stack操作：
push：將資料放入堆疊的頂點（串列形式），不進行輸出。
pop：將堆疊頂端資料輸出，並刪除頂點節點，假如堆疊是空的則輸出"Stack is empty"。
top：將堆疊頂端資料輸出，假如堆疊是空的則輸出"Stack is empty"。
empty：將堆疊中所有節點刪除，假如堆疊是空的則輸出"Stack is empty"，不進行輸出。
print：將堆疊中所有節點資料從頂點到底部依序輸出data，假如堆疊是空的則輸出"Stack
is empty"。

【輸入說明】
第一行，輸入一整數 N ( 1 <= N <= 20 )，代表有N個操作。
第二行~第2+N行，輸入操作的種類
push操作：push data，push為字串，data為整數(0<=data<=100)，中間以空白隔開
pop操作：pop，pop為字串
top操作：top，top為字串
empty操作：empty，empty為字串
print操作：print，print為字串

範例輸入說明:
13 (N為13，代表有13個操作)
push 1 (在Stack的頂點加入一個data為1的節點)
push 2 (在Stack的頂點加入一個data為2的節點)
top (將Stack頂端data輸出)
push 3 (在Stack的頂點加入一個data為3的節點)
push 4 (在Stack的頂點加入一個data為4的節點)
top (將Stack頂端data輸出)
pop (將Stack頂端data輸出，並刪除頂點節點)
top (將Stack頂端data輸出)
pop (將Stack頂端data輸出，並刪除頂點節點)
top (將Stack頂端data輸出)
empty (將Stack中所有節點刪除)
top (將Stack頂端data輸出)
empty (將Stack中所有節點刪除)

【輸出說明】
第一行~第N行，根據操作輸出對應的data

範例輸出說明:
2 (根據輸入的操作1、2，目前頂點節點的data為2)
4 (根據輸入的操作4、5，目前頂點節點的data為4)
4 (目前頂點節點的data為4，輸出並刪除該節點)
3 (目前頂點節點的data為3)
3 (目前頂點節點的data為3，輸出並刪除該節點)
2 (目前頂點節點的data為2)
Stack is empty (在操作11時，已將Stack中所有節點刪除，故為空)
Stack is empty (在操作11時，已將Stack中所有節點刪除，故為空)

【測試資料一】
輸入：
13
top
empty
top
pop
pop
pop
empty
push 38
print
top
push 77
top
pop

輸出：
Stack is empty
Stack is empty
Stack is empty
Stack is empty
Stack is empty
Stack is empty
Stack is empty
38
38
77
77

【測試資料二】
輸入：
17
push 28
top
push 36
empty
empty
top
print
push 47
push 41
push 17
print
push 51
push 28
top
empty
pop
push 80

輸出：
28
Stack is empty
Stack is empty
Stack is empty
17
41
47
28
Stack is empty

【測試資料三】
輸入：
11
print
push 64
push 52
pop
pop
top
print
push 46
empty
push 7
pop

輸出：
Stack is empty
52
64
Stack is empty
Stack is empty
7

【測試資料四】
輸入：
10
push 87
push 63
print
push 99
push 45
push 62
push 50
top
pop
top

輸出：
63
87
50
50
62

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_s {
  int data;
  struct node_s *next;
} node_t;

typedef node_t *nodep_t;

nodep_t stack = NULL;

void push(int data) {
  nodep_t newNode = (nodep_t)malloc(sizeof(node_t));
  newNode->data = data;
  newNode->next = stack;
  stack = newNode;
}

void pop() {
  if (stack == NULL) {
    printf("Stack is empty\n");
  } else {
    nodep_t temp = stack;
    printf("%d\n", stack->data);
    stack = stack->next;
    free(temp);
  }
}

void top() {
  if (stack == NULL) {
    printf("Stack is empty\n");
  } else {
    printf("%d\n", stack->data);
  }
}

void empty() {
  if (stack == NULL) {
    printf("Stack is empty\n");
  } else {
    while (stack != NULL) {
      nodep_t temp = stack;
      stack = stack->next;
      free(temp);
    }
  }
}

void print() {
  if (stack == NULL) {
    printf("Stack is empty\n");
  } else {
    nodep_t current = stack;
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
    } else if (strcmp(command, "top") == 0) {
      top();
    } else if (strcmp(command, "empty") == 0) {
      empty();
    } else if (strcmp(command, "print") == 0) {
      print();
    }
  }

  // Clean up any remaining nodes in the stack
  // empty();
  return 0;
}
