/*
034 創建唯一二元樹
本題必須使用Link List實作，否則不予計分。

Link List 架構:
typedef struct node_s {
char data;
struct node_s * right, * left;
} tree_t;
typedef tree_t * btree;


給定前序或後序以及中序，請建構唯一的Binary Tree(非二元搜尋樹)。
輸出該Tree的內容，輸出順序為由上而下，由左而右印出。

前序或後序以及中序代號分別為:
前序代號：P
中序代號：I
後序代號：O

【輸入說明】
第一行輸入前序、中序或後序的代號。
第二行輸入上一行輸入尋訪的字串結果A(1<=A的字串長度<=20)，結果皆為大寫英文字母。
第三行輸入前序、中序或後序的代號。
第四行輸入上一行輸入尋訪的字串結果B(1<=B的字串長度<=20)。

範例輸入說明:
P (下一行輸入前序結果)
ADFGECB (前序尋訪Tree的結果)
I (下一行輸入中序結果)
ABDCFEG (中序尋訪Tree的結果)

【輸出說明】
輸出唯一二元樹的內容，輸出順序為由上而下，由左而右。

範例輸出說明:
BACDEFG (唯一二元樹由上而下，由左而右的輸出結果)。

【測試資料一】
輸入:
P
ABDHIEJKCFLMGNO
I
HDIBJEKALFMCNGO

輸出:
ABCDEFGHIJKLMNO

【測試資料二】
輸入:
P
JKEWVBMXYZ
I
ZYXMBVWEKJ

輸出:
JKEWVBMXYZ

【測試資料三】
輸入:
P
TAVHKOLPWS
I
TAVHKOLPWS

輸出:
TAVHKOLPWS

【測試資料四】
輸入:
P
IKQRPLTEHMZCFD
I
QRKLPTIMHZEFCD

輸出:
IKEQPHCRLTMZFD

【測試資料五】
輸入:
P
CKQWGLTEHOZIFD
I
WQKLGTCOHZEFID

輸出:
CKEQGHIWLTOZFD

【測試資料六】
輸入:
I
HDIBJEKALFMCNGO
O
HIDJKEBLMFNOGCA

輸出:
ABCDEFGHIJKLMNO

【測試資料七】
輸入:
I
QKJEG
O
QKJEG

輸出:
GEJKQ

【測試資料八】
輸入:
I
TFCAO
O
OACFT

輸出:
TFCAO

【測試資料九】
輸入:
I
RBKDCGAHTIQLFM
O
BRDGCKHITLMFQA

輸出:
AKQRCTFBDGHILM

【測試資料十】
輸入:
I
ZBTLANPDOKFHRI
O
ZBLNATDKOHIRFP

輸出:
PTFBAORZLNDKHI

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義樹節點結構
typedef struct node_s {
  char data;
  struct node_s *left, *right;
} tree_t;

typedef tree_t *btree;

// 創建新節點
btree newNode(char data) {
  btree node = (btree)malloc(sizeof(tree_t));
  node->data = data;
  node->left = node->right = NULL;
  return node;
}

// 查找字符在中序遍歷中的索引
int search(char arr[], int strt, int end, char value) {
  for (int i = strt; i <= end; i++) {
    if (arr[i] == value)
      return i;
  }
  return -1;
}

// 使用前序和中序遍歷結果構建二元樹
btree PreIn(char in[], char pre[], int inStrt, int inEnd, int *preIndex) {
  if (inStrt > inEnd)
    return NULL;

  btree tNode = newNode(pre[*preIndex]);
  (*preIndex)++;

  if (inStrt == inEnd)
    return tNode;

  int inIndex = search(in, inStrt, inEnd, tNode->data);

  tNode->left = PreIn(in, pre, inStrt, inIndex - 1, preIndex);
  tNode->right = PreIn(in, pre, inIndex + 1, inEnd, preIndex);

  return tNode;
}

// 使用後序和中序遍歷結果構建二元樹
btree PostIn(char in[], char post[], int inStrt, int inEnd, int *postIndex) {
  if (inStrt > inEnd)
    return NULL;

  btree tNode = newNode(post[*postIndex]);
  (*postIndex)--;

  if (inStrt == inEnd)
    return tNode;

  int inIndex = search(in, inStrt, inEnd, tNode->data);

  tNode->right = PostIn(in, post, inIndex + 1, inEnd, postIndex);
  tNode->left = PostIn(in, post, inStrt, inIndex - 1, postIndex);

  return tNode;
}

// 打印樹的層次遍歷結果
void printOrder(btree root) {
  if (root == NULL)
    return;

  btree queue[20];
  int front = 0, rear = 0;
  queue[rear++] = root;

  while (front < rear) {
    btree current = queue[front++];

    printf("%c", current->data);

    if (current->left != NULL)
      queue[rear++] = current->left;
    if (current->right != NULL)
      queue[rear++] = current->right;
  }
  printf("\n");
}

int main() {
  char order1, order2;
  char seq1[21], seq2[21];

  scanf(" %c", &order1);
  scanf("%s", seq1);
  scanf(" %c", &order2);
  scanf("%s", seq2);

  btree root = NULL;
  int len = strlen(seq1);

  if (order1 == 'P' && order2 == 'I') {
    int preIndex = 0;
    root = PreIn(seq2, seq1, 0, len - 1, &preIndex);
  } else if (order1 == 'I' && order2 == 'P') {
    int preIndex = 0;
    root = PreIn(seq1, seq2, 0, len - 1, &preIndex);
  } else if (order1 == 'O' && order2 == 'I') {
    int postIndex = len - 1;
    root = PostIn(seq2, seq1, 0, len - 1, &postIndex);
  } else if (order1 == 'I' && order2 == 'O') {
    int postIndex = len - 1;
    root = PostIn(seq1, seq2, 0, len - 1, &postIndex);
  }

  printOrder(root);

  return 0;
}
