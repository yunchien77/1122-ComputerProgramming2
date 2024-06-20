/*
35. 開發專案

本題必須使用Link List實作，否則不予計分。

Link List 架構:
typedef struct node_s{
int time;
int waiteNodeNum;
int waiteNode[100];
struct node_s* next;
}node_t;
typedef node_t* nodep;

開發專案時，
專案會被分割為許多項目，分配給多組程式設計師開發。
這些項目有順序關係，且只有當順序在前的項目完成，才能開始開發順序在後的項目。

本題使用一個有向無環圖，表示這些項目的開發順序。
每個節點代表一個項目，節點內的數字為節點編號，
上方所列數字代表開發這個項目所需天數；
邊表示開發順序。

以下方圖示為例，只有在節點2完成後，才能開始節點4的開發。
同理，只有在節點3與節點4都完成後，才能開始節點5的開發。



請根據開發流程圖，計算該專案要多少天才能完成。


【輸入說明】
第一行為整數 N，代表有 N 組專案 ( 1 <= N <= 3 )。
第二行為整數 M，代表該專案共有 M 個工作事項 (節點) ( 2 <= M <= 100 )。
接下來 M 行，每一行依序代表一個項目節點 (從第1個節點開始)，
第一個整數表示完成這個項目節點所需的天數，
第二個整數 K ，表示這個節點有 K 個節點正在等待該項目完成，
接下來 K 個整數表示該項目所指向的每個項目編號，字元間以空白相隔開。
若 K 為 0 ，則代表沒有項目在等待，不需輸入項目編號。

第 M+1 行後，繼續輸入下一組專案資訊，
輸入方式以此類推，直到第 N 組專案結束。

範例輸入:
2 (有2組專案)
2 (第一個專案有2個工作事項)
8 1 2
(第1個工作事項需要8天完成，有1個工作事項在等待該項目完成，第2工作事項正在等待)
2 0 (第2個工作事項需要2天完成，沒有工作事項在等待該項目完成)
5 (第二個專案有5個工作事項)
6 2 2 3
(第1個工作事項需要6天完成，有2個工作事項在等待該項目完成，第2、3工作事項正在等待)
5 1 4
(第2個工作事項需要5天完成，有1個工作事項在等待該項目完成，第4工作事項正在等待)
11 1 5
(第3個工作事項需要11天完成，有1個工作事項在等待該項目完成，第5工作事項正在等待)
4 1 5
(第4個工作事項需要4天完成，有1個工作事項在等待該項目完成，第5工作事項正在等待)
8 0 (第5個工作事項需要8天完成，沒有工作事項在等待該項目完成)

【輸出說明】
第一行輸出第一組專案開發所需的時間。
第二行輸出第二組專案開發所需的時間。
以此類推，直到 N 行。

範例輸出:
10 (第一組專案需要10天)
25 (第二組專案需要25天)

【測試資料一】
輸入 :
2
2
8 1 2
2 0
5
6 2 2 3
5 1 4
11 1 5
4 1 5
8 0

輸出 :
10
25


【測試資料二】
輸入 :
1
11
1 2 2 4
2 1 3
3 2 4 5
4 1 5
5 1 6
6 3 7 8 9
7 2 8 10
8 2 9 10
9 1 11
10 1 11
11 0

輸出 :
57

【測試資料三】
輸入 :
1
9
1 1 2
6 2 3 4
5 2 4 5
11 1 6
4 1 6
8 2 7 9
9 1 8
1 1 9
10 0

輸出 :
51

【測試資料四】
輸入 :
1
100
1 1 2
2 1 3
3 1 4
4 1 5
5 1 6
6 1 7
7 1 8
8 1 9
9 1 10
10 1 11
11 1 12
12 1 13
13 1 14
14 1 15
15 1 16
16 1 17
17 1 18
18 1 19
19 1 20
20 1 21
21 1 22
22 1 23
23 1 24
24 1 25
25 1 26
26 1 27
27 1 28
28 1 29
29 1 30
30 1 31
31 1 32
32 1 33
33 1 34
34 1 35
35 1 36
36 1 37
37 1 38
38 1 39
39 1 40
40 1 41
41 1 42
42 1 43
43 1 44
44 1 45
45 1 46
46 1 47
47 1 48
48 1 49
49 1 50
50 1 51
51 1 52
52 1 53
53 1 54
54 1 55
55 1 56
56 1 57
57 1 58
58 1 59
59 1 60
60 1 61
61 1 62
62 1 63
63 1 64
64 1 65
65 1 66
66 1 67
67 1 68
68 1 69
69 1 70
70 1 71
71 1 72
72 1 73
73 1 74
74 1 75
75 1 76
76 1 77
77 1 78
78 1 79
79 1 80
80 1 81
81 1 82
82 1 83
83 1 84
84 1 85
85 1 86
86 1 87
87 1 88
88 1 89
89 1 90
90 1 91
91 1 92
92 1 93
93 1 94
94 1 95
95 1 96
96 1 97
97 1 98
98 1 99
99 1 100
100 0

輸出 :
5050


【測試資料五】
輸入 :
1
8
3 2 2 8
4 2 3 8
5 2 4 8
6 2 5 8
7 2 6 8
8 2 7 8
9 1 8
20 0

輸出 :
62


【測試資料六】
輸入 :
1
20
1 0
3 0
5 0
7 0
9 0
11 0
13 0
15 0
17 0
19 0
21 0
23 0
25 0
27 0
29 0
31 0
33 0
35 0
37 0
39 0

輸出 :
39


【測試資料七】
輸入 :
1
10
1 3 2 3 4
10 1 5
15 1 5
20 1 5
5 3 6 7 8
16 1 9
14 1 9
27 1 9
7 1 10
12 0

輸出 :
72


【測試資料八】
輸入 :
1
7
2 2 2 3
3 1 4
6 1 5
11 2 6 7
9 1 7
10 0
7 0

輸出 :
26

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef struct node_s {
  int time;
  int waiteNodeNum;
  int waiteNode[MAX];
  struct node_s *next;
} node_t;

typedef node_t *nodep;

typedef struct project_s {
  int numNodes;
  nodep nodes[MAX];
} project_t;

nodep createNode(int time, int waiteNodeNum, int waiteNode[]) {
  nodep newNode = (nodep)malloc(sizeof(node_t));
  newNode->time = time;
  newNode->waiteNodeNum = waiteNodeNum;
  for (int i = 0; i < waiteNodeNum; i++) {
    newNode->waiteNode[i] = waiteNode[i];
  }
  newNode->next = NULL;
  return newNode;
}

project_t *createProject(int numNodes) {
  project_t *project = (project_t *)malloc(sizeof(project_t));
  project->numNodes = numNodes;
  for (int i = 0; i < numNodes; i++) {
    project->nodes[i] = NULL;
  }
  return project;
}

void addNodeToProject(project_t *project, int nodeIndex, int time,
                      int waiteNodeNum, int waiteNode[]) {
  project->nodes[nodeIndex] = createNode(time, waiteNodeNum, waiteNode);
}

int findCompletionTime(project_t *project) {
  int indegree[MAX] = {0};
  int completionTime[MAX] = {0};

  // 計算每個節點的入度
  for (int i = 0; i < project->numNodes; i++) {
    nodep node = project->nodes[i];
    for (int j = 0; j < node->waiteNodeNum; j++) {
      indegree[node->waiteNode[j] - 1]++;
    }
  }

  // 使用隊列進行拓撲排序
  int queue[MAX];
  int front = 0, rear = 0;

  // 將入度為0的節點加入隊列
  for (int i = 0; i < project->numNodes; i++) {
    if (indegree[i] == 0) {
      queue[rear++] = i;
      completionTime[i] = project->nodes[i]->time;
    }
  }

  while (front < rear) {
    int current = queue[front++];
    nodep node = project->nodes[current];
    for (int i = 0; i < node->waiteNodeNum; i++) {
      int nextNode = node->waiteNode[i] - 1;
      indegree[nextNode]--;
      if (completionTime[nextNode] <
          completionTime[current] + project->nodes[nextNode]->time) {
        completionTime[nextNode] =
            completionTime[current] + project->nodes[nextNode]->time;
      }
      if (indegree[nextNode] == 0) {
        queue[rear++] = nextNode;
      }
    }
  }

  // 找到最大完成時間
  int maxTime = 0;
  for (int i = 0; i < project->numNodes; i++) {
    if (completionTime[i] > maxTime) {
      maxTime = completionTime[i];
    }
  }

  return maxTime;
}

int main() {
  int N;
  scanf("%d", &N);

  for (int i = 0; i < N; i++) {
    int M;
    scanf("%d", &M);
    project_t *project = createProject(M);

    for (int j = 0; j < M; j++) {
      int time, K;
      scanf("%d %d", &time, &K);
      int waiteNode[MAX] = {0};
      for (int k = 0; k < K; k++) {
        scanf("%d", &waiteNode[k]);
      }
      addNodeToProject(project, j, time, K, waiteNode);
    }

    int result = findCompletionTime(project);
    printf("%d\n", result);
    free(project);
  }

  return 0;
}
