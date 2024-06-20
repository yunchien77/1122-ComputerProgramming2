/*
33. 城市旅遊

假設一個國家內有多個城市，城市之間會透過N條道路相互連通。根據輸入的兩個城市：起始城市X和目的城市Z。你需要找出從X到Z的一條最短路徑。此外，題目可能還會指定一個必經城市Y，如果有給定城市Y，則從X到Z的路徑必須經過Y，並找出X到Y再到Z的最短路徑。如果沒有給定必經城市Y，則找出從X到Z的最短路徑就好。

不考慮同時有多條最短路徑

【輸入說明】
第一行：輸入N, X, Z, Y，N 代表道路數量(3<=N<=15)，X 代表起始點城市，Z
代表終點城市，Y 代表必經城市，若沒有 Y，則不考慮中途點，中間以空白隔開。
第二行~N+1行：每一行輸入格式為 A B，代表 A 城市與 B
城市間有道路相連接，中間以空白隔開。

範例輸入說明:
3 1 3 (國家內有 3 條道路，要從起始點城市 1 到達終點城市 3，沒有必須經過的城市)
1 5 (城市 1 和城市 5 之間有一條道路)
7 5 (城市 7 和城市 5 之間有一條道路)
7 3 (城市 7 和城市 3 之間有一條道路)

【輸出說明】
若存在，則第一行輸出經過最少道路個數，第二行輸出最短路徑。
若不存在此路徑，輸出 NO。

範例輸出說明:
3 (總共經過3個道路)
1 5 7 3 (城市 1 到城市 3 能找到的最短路徑為 1 -> 5 -> 7 -> 3)

【測試資料一】
輸入:
6 1 3
1 5
7 5
4 5
3 5
2 3
4 3

輸出:
2
1 5 3

【測試資料二】
輸入:
6 1 4 3
1 2
1 3
2 4
2 5
3 5
5 4

輸出:
3
1 3 5 4

【測試資料三】
輸入:
15 1 15
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
7 15
14 15

輸出:
7
1 2 3 4 5 6 7 15

【測試資料四】
輸入:
13 1 10 4
1 4
1 5
2 4
3 5
3 4
3 2
4 3
5 2
6 3
7 10
8 7
9 7
10 8

輸出:
NO

【測試資料五】
輸入:
7 1 10
1 4
1 5
2 4
3 5
6 3
7 10
10 8

輸出:
NO

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define INF 1000000

typedef struct Node {
  int vertex;
  struct Node *next;
} Node;

typedef struct Graph {
  int numVertices;
  Node **adjLists;
} Graph;

typedef struct Queue {
  int items[MAX];
  int front;
  int rear;
} Queue;

Node *createNode(int v) {
  Node *newNode = malloc(sizeof(Node));
  newNode->vertex = v;
  newNode->next = NULL;
  return newNode;
}

Graph *createGraph(int vertices) {
  Graph *graph = malloc(sizeof(Graph));
  graph->numVertices = vertices;
  graph->adjLists = malloc(vertices * sizeof(Node *));
  for (int i = 0; i < vertices; i++) {
    graph->adjLists[i] = NULL;
  }
  return graph;
}

void addEdge(Graph *graph, int src, int dest) {
  Node *newNode = createNode(dest);
  newNode->next = graph->adjLists[src];
  graph->adjLists[src] = newNode;

  newNode = createNode(src);
  newNode->next = graph->adjLists[dest];
  graph->adjLists[dest] = newNode;
}

Queue *createQueue() {
  Queue *q = malloc(sizeof(Queue));
  q->front = -1;
  q->rear = -1;
  return q;
}

int isEmpty(Queue *q) {
  if (q->rear == -1)
    return 1;
  else
    return 0;
}

void enqueue(Queue *q, int value) {
  if (q->rear == MAX - 1)
    return;
  else {
    if (q->front == -1)
      q->front = 0;
    q->rear++;
    q->items[q->rear] = value;
  }
}

int dequeue(Queue *q) {
  int item;
  if (isEmpty(q)) {
    return -1;
  } else {
    item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
      q->front = q->rear = -1;
    }
    return item;
  }
}

void printPath(int parent[], int j) {
  if (parent[j] == -1)
    return;
  printPath(parent, parent[j]);
  printf(" %d", j);
}

int BFS(Graph *graph, int startVertex, int endVertex, int parent[]) {
  int visited[graph->numVertices];
  memset(visited, 0, sizeof(visited));

  Queue *queue = createQueue();
  visited[startVertex] = 1;
  enqueue(queue, startVertex);
  parent[startVertex] = -1;

  while (!isEmpty(queue)) {
    int currentVertex = dequeue(queue);

    Node *temp = graph->adjLists[currentVertex];
    while (temp) {
      int adjVertex = temp->vertex;

      if (!visited[adjVertex]) {
        visited[adjVertex] = 1;
        parent[adjVertex] = currentVertex;
        enqueue(queue, adjVertex);

        if (adjVertex == endVertex)
          return 1;
      }
      temp = temp->next;
    }
  }
  return 0;
}

void findShortestPath(Graph *graph, int start, int end) {
  int parent[graph->numVertices];
  if (BFS(graph, start, end, parent)) {
    int pathLength = 0;
    int temp = end;
    while (parent[temp] != -1) {
      pathLength++;
      temp = parent[temp];
    }
    printf("%d\n", pathLength);
    printf("%d", start);
    printPath(parent, end);
    printf("\n");
  } else {
    printf("NO\n");
  }
}

void findShortestPathWithIntermediate(Graph *graph, int start, int intermediate,
                                      int end) {
  int parent1[graph->numVertices], parent2[graph->numVertices];
  if (BFS(graph, start, intermediate, parent1) &&
      BFS(graph, intermediate, end, parent2)) {
    int pathLength1 = 0, pathLength2 = 0;
    int temp = intermediate;
    while (parent1[temp] != -1) {
      pathLength1++;
      temp = parent1[temp];
    }
    temp = end;
    while (parent2[temp] != -1) {
      pathLength2++;
      temp = parent2[temp];
    }
    printf("%d\n", pathLength1 + pathLength2);
    printf("%d", start);
    printPath(parent1, intermediate);
    printPath(parent2, end);
    printf("\n");
  } else {
    printf("NO\n");
  }
}

int main() {
  int N, X, Z, Y = -1;
  char buffer[20];
  fgets(buffer, sizeof(buffer), stdin);
  if (strchr(buffer, '\n') != NULL) {
    sscanf(buffer, "%d %d %d %d", &N, &X, &Z, &Y);
  } else {
    sscanf(buffer, "%d %d %d", &N, &X, &Z);
    Y = -1;
  }

  Graph *graph = createGraph(MAX);

  for (int i = 0; i < N; i++) {
    int A, B;
    scanf("%d %d", &A, &B);
    addEdge(graph, A, B);
  }

  if (Y != -1) {
    findShortestPathWithIntermediate(graph, X, Y, Z);
  } else {
    findShortestPath(graph, X, Z);
  }

  return 0;
}
