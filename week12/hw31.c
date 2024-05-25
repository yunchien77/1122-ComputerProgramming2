/*
31 LinkList多項式運算
本題必須使用Link List實作，否則不予計分。

題目給定兩個多項式，請輸出兩個多項式相加、相減、相乘的結果。

多項式運算結果輸出規範:
1. 輸出計算後從最高次方到0次方的結果。
2. 每一項須輸出係數、x、x的次方數，

每一項輸出格式如下:
1. x的次方數 > 1，輸出ax^k (a為係數，k為次方數)
2. x的次方數 = 1，輸出ax (a為係數)
3. x的次方數 = 0，輸出a (a為係數)
4. 如果所有係數都為0，則該行輸出0

每一項正負號規範:
1. 若該項係數為0，不輸出該項。
2. 若該項的次方數不為多項式的最高次方數，則該項根據係數值的正負數輸出對應的 "+"
或 "-"。
3. 若該項的係數值為1或-1，則不輸出係數值，僅輸出對應的 "+" 或 "-"。



【輸入說明】
輸入共兩行，每行各代表一個多項式。
每一行輸入 n 個整數，第一個數字代表多項式中 n-1次方項的係數，第 n 個代表多項式中
0 次方項的係數。

範例輸入說明:
2 3 0 1 -1 (代表輸入的多項式為2x^4 + 3x^3 + x -1)
1 0 -1 4 -3 2 (代表輸入的多項式為x^5 - x^3 + 4x^2 - 3x +2)



【輸出說明】
第一行輸出兩個多項式相加的結果
第二行輸出兩個多項式相減的結果
第三行輸出兩個多項式相乘的結果
備註：輸出須符合題目敘述的多項式運算結果輸出規範

範例輸出說明:
x^5+2x^4+2x^3+4x^2-2x+1 (2x^4 + 3x^3 + x - 1 + x^5 - x^3 + 4x^2 - 3x + 2的結果)
-x^5+2x^4+4x^3-4x^2+4x-3 (2x^4 + 3x^3 + x - 1 - x^5 - x^3 + 4x^2 - 3x + 2的結果)
2x^9+3x^8-2x^7+6x^6+5x^5-6x^4+11x^3-7x^2+5x-2 ((2x^4 + 3x^3 + x - 1) * (x^5 -
x^3 + 4x^2 - 3x + 2)的結果)

【測試資料一】
輸入:
2 3 0 1 -1
1 0 -1 4 -3 2

輸出:
x^5+2x^4+2x^3+4x^2-2x+1
-x^5+2x^4+4x^3-4x^2+4x-3
2x^9+3x^8-2x^7+6x^6+5x^5-6x^4+11x^3-7x^2+5x-2

【測試資料二】
輸入:
3 -7 1 2
7 -1 4

輸出:
3x^3+6
3x^3-14x^2+2x-2
21x^5-52x^4+26x^3-15x^2+2x+8

【測試資料三】
輸入:
0 0 0 0 0 0 0
1 2 3 4 5 6 7 8

輸出:
x^7+2x^6+3x^5+4x^4+5x^3+6x^2+7x+8
-x^7-2x^6-3x^5-4x^4-5x^3-6x^2-7x-8
0

【測試資料四】
輸入:
100 2 3 90 20 -123
5 9 -1 -2 0 0

輸出:
105x^5+11x^4+2x^3+88x^2+20x-123
95x^5-7x^4+4x^3+92x^2+20x-123
500x^10+910x^9-67x^8+275x^7+903x^6-531x^5-1307x^4+83x^3+246x^2

【測試資料五】
輸入:
1 0 0 1
1 0 0 1

輸出:
2x^3+2
0
x^6+2x^3+1

【測試資料六】
輸入:
-1 0 0 -1
1 0 0 1

輸出:
0
-2x^3-2
-x^6-2x^3-1

【測試資料七】
輸入:
0
0

輸出:
0
0
0

【測試資料八】
輸入:
1 1 0 0
1 1

輸出:
x^3+x^2+x+1
x^3+x^2-x-1
x^4+2x^3+x^2

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

// 定義多項式節點結構
typedef struct PolyNode {
  int coef; // 係數
  int exp;  // 次方
  struct PolyNode *next;
} PolyNode;

// 創建新節點
PolyNode *createNode(int coef, int exp) {
  PolyNode *newNode = (PolyNode *)malloc(sizeof(PolyNode));
  newNode->coef = coef;
  newNode->exp = exp;
  newNode->next = NULL;
  return newNode;
}

// 插入節點到鏈結串列（依次方遞減順序）
PolyNode *insertNode(PolyNode *head, int coef, int exp) {
  if (coef == 0)
    return head; // 不插入係數為0的項
  PolyNode *newNode = createNode(coef, exp);
  if (!head || head->exp < exp) {
    newNode->next = head;
    return newNode;
  }
  PolyNode *current = head;
  while (current->next && current->next->exp > exp) {
    current = current->next;
  }
  if (current->exp == exp) {
    current->coef += coef;
    if (current->coef == 0) {
      PolyNode *temp = current->next;
      current->next = current->next->next;
      free(temp);
    }
    free(newNode);
  } else {
    newNode->next = current->next;
    current->next = newNode;
  }
  return head;
}

// 讀取多項式
PolyNode *readPolynomial() {
  char line[MAX_LINE_LENGTH];
  fgets(line, MAX_LINE_LENGTH, stdin);

  PolyNode *poly = NULL;
  int coef;
  int exp = 0;
  int termCount = 0;

  // 首先复制输入行以便多次解析
  char lineCopy[MAX_LINE_LENGTH];
  strcpy(lineCopy, line);

  // 計算多項式項數
  for (char *token = strtok(line, " "); token != NULL;
       token = strtok(NULL, " ")) {
    termCount++;
  }

  // 再次解析多項式，並插入節點
  exp = termCount - 1;
  for (char *token = strtok(lineCopy, " "); token != NULL;
       token = strtok(NULL, " ")) {
    coef = atoi(token);
    poly = insertNode(poly, coef, exp);
    exp--;
  }

  return poly;
}

// 打印多項式
void printPolynomial(PolyNode *poly) {
  int first = 1;
  while (poly) {
    if (poly->coef) {
      if (!first && poly->coef > 0)
        printf("+");
      if (poly->coef == -1 && poly->exp != 0)
        printf("-");
      if (abs(poly->coef) != 1 || poly->exp == 0)
        printf("%d", poly->coef);
      if (poly->exp > 1)
        printf("x^%d", poly->exp);
      if (poly->exp == 1)
        printf("x");
      first = 0;
    }
    poly = poly->next;
  }
  if (first)
    printf("0");
  printf("\n");
}

// 多項式相加
PolyNode *addPolynomials(PolyNode *poly1, PolyNode *poly2) {
  PolyNode *result = NULL;
  while (poly1 || poly2) {
    int coef = 0, exp = 0;
    if (poly1 && (!poly2 || poly1->exp > poly2->exp)) {
      coef = poly1->coef;
      exp = poly1->exp;
      poly1 = poly1->next;
    } else if (poly2 && (!poly1 || poly2->exp > poly1->exp)) {
      coef = poly2->coef;
      exp = poly2->exp;
      poly2 = poly2->next;
    } else {
      coef = poly1->coef + poly2->coef;
      exp = poly1->exp;
      poly1 = poly1->next;
      poly2 = poly2->next;
    }
    result = insertNode(result, coef, exp);
  }
  return result;
}

// 多項式相減
PolyNode *subtractPolynomials(PolyNode *poly1, PolyNode *poly2) {
  PolyNode *result = NULL;
  while (poly1 || poly2) {
    int coef = 0, exp = 0;
    if (poly1 && (!poly2 || poly1->exp > poly2->exp)) {
      coef = poly1->coef;
      exp = poly1->exp;
      poly1 = poly1->next;
    } else if (poly2 && (!poly1 || poly2->exp > poly1->exp)) {
      coef = -poly2->coef;
      exp = poly2->exp;
      poly2 = poly2->next;
    } else {
      coef = poly1->coef - poly2->coef;
      exp = poly1->exp;
      poly1 = poly1->next;
      poly2 = poly2->next;
    }
    result = insertNode(result, coef, exp);
  }
  return result;
}

// 多項式相乘
PolyNode *multiplyPolynomials(PolyNode *poly1, PolyNode *poly2) {
  PolyNode *result = NULL;
  for (PolyNode *p1 = poly1; p1; p1 = p1->next) {
    for (PolyNode *p2 = poly2; p2; p2 = p2->next) {
      result = insertNode(result, p1->coef * p2->coef, p1->exp + p2->exp);
    }
  }

  // 合併具有相同次方的節點
  PolyNode *current = result;
  while (current != NULL && current->next != NULL) {
    if (current->exp == current->next->exp) {
      current->coef += current->next->coef;
      // 刪除重複的節點
      PolyNode *temp = current->next;
      current->next = current->next->next;
      free(temp);
    } else {
      current = current->next;
    }
  }
  return result;
}

// 清除多項式節點
void clearPolynomial(PolyNode *poly) {
  while (poly) {
    PolyNode *temp = poly;
    poly = poly->next;
    free(temp);
  }
}

void printList(PolyNode *head) {
  while (head) {
    printf("(%d, %d) -> ", head->coef, head->exp);
    head = head->next;
  }
  printf("NULL\n");
}

int main() {
  // 讀取兩個多項式
  PolyNode *poly1 = readPolynomial();
  // printList(poly1);
  PolyNode *poly2 = readPolynomial();
  // printList(poly2);

  // 計算並打印結果
  PolyNode *sum = addPolynomials(poly1, poly2);
  PolyNode *diff = subtractPolynomials(poly1, poly2);
  PolyNode *prod = multiplyPolynomials(poly1, poly2);

  printPolynomial(sum);
  printPolynomial(diff);
  printPolynomial(prod);

  // 釋放記憶體
  clearPolynomial(poly1);
  clearPolynomial(poly2);
  clearPolynomial(sum);
  clearPolynomial(diff);
  clearPolynomial(prod);

  return 0;
}
