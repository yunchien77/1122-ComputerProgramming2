/*
026 邏輯電路圖

輸入的邏輯閘種類代號如下：
A：AND Gate
O：OR Gate
N：NOT Gate
B：BUFFER Gate

X1 -->P_Gate----------------------------->Y1
X2 ----------------->Q_Gate--------------->Y2
X3 --------------------------------R_Gate--->Y3
上方為邏輯電路範例圖，
電路輸入為 X1, X2, X3，
設定 P_Gate、Q_Gate、R_Gate三個邏輯閘
電路輸出為 Y1, Y2, Y3
1. P_Gate 邏輯閘可設定為 NOT或BUFFER,輸入為 X1,輸出為 Y1和Q_Gate 邏輯閘的輸入。
2. Q_Gate 邏輯閘可設定為 AND 或 OR,輸入為 X2 和 P_Gate 邏輯閘的輸出,輸出為 Y2 和
R_Gate 邏輯閘的輸入。
3. R_Gate 邏輯閘可設定為 AND 或 OR,輸入為 X3 和 Q_Gate 邏輯閘的輸出,輸出為 Y3。
4. 輸入 X1、X2、X3,以及設定P_Gate、Q_Gate、R_Gate三個邏輯閘的種類。

本題必須使用給定程式碼架構實作，否則將不予計分。
解題時可針對範例的架構程式碼做修改，但需符合以下三點：
1. #define中必須定義函數指標，函數的參數可自行決定
2. 有定義struct，且當中有使用到第一點的define
3. 使用struct的函數指標進行本題的實作

#define GATEVALUE(Gate) int(*GateValue)()
typedef struct _Gate {
int input1;
int input2;
GATEVALUE(Gate);
}Gate;
int GateORValue(Gate *gate) {
...
}
int GateANDValue(Gate *gate) {
...
}
int GateNOTValue(Gate *gate) {
...
}
int GateBUFFERValue(Gate *gate) {
...
}
void CreateGate(Gate *obj, char type, int input1, int input2) {
...
}

【輸入說明】
第一行輸入字串，代表X1, X2, X3的數值，中間以空白隔開
第二行輸入字串，代表P_Gate, Q_Gate, R_Gate的數值，中間以空白隔開

範例輸入說明:
1 0 1 (X1=1, X2=0, X3=1)
N A O (P_Gate=NOT gate, Q_Gate=AND gate, R_Gate=OR gate)

【輸出說明】
第一行輸出Y1, Y2, Y3經過運算的結果，中間以空白隔開

範例輸出說明:
0 0 1 (X1進行NOT運算得到1，Y1和X2進行AND運算得到0，Y2和X3進行AND運算得到1)

【測試資料一】
輸入：
0 0 0
N A A

輸出：
1 0 0

【測試資料二】
輸入：
1 0 1
B O O

輸出：
1 1 1

【測試資料三】
輸入：
1 1 0
N A O

輸出：
0 0 0

【測試資料四】
輸入：
0 1 1
B O A

輸出：
0 1 1

*/

#include <stdio.h>
#include <stdlib.h>

#define GATEVALUE(TYPE) int (*GateValue)(struct _##TYPE *)

typedef struct _Gate {
  int input1;
  int input2;
  GATEVALUE(Gate);
} Gate;

int GateORValue(Gate *gate) { return gate->input1 || gate->input2; }

int GateANDValue(Gate *gate) { return gate->input1 && gate->input2; }

int GateNOTValue(Gate *gate) { return !(gate->input1); }

int GateBUFFERValue(Gate *gate) { return gate->input1; }

void CreateGate(Gate *obj, char type, int input1, int input2) {
  obj->input1 = input1;
  obj->input2 = input2;
  switch (type) {
  case 'A':
    obj->GateValue = (int (*)(Gate *))GateANDValue;
    break;
  case 'O':
    obj->GateValue = (int (*)(Gate *))GateORValue;
    break;
  case 'N':
    obj->GateValue = (int (*)(Gate *))GateNOTValue;
    break;
  case 'B':
    obj->GateValue = (int (*)(Gate *))GateBUFFERValue;
    break;
  default:
    obj->GateValue = NULL;
    break;
  }
}

int main() {
  int X1, X2, X3;
  char P_type, Q_type, R_type;

  scanf("%d %d %d", &X1, &X2, &X3);
  scanf(" %c %c %c", &P_type, &Q_type, &R_type);

  Gate P_Gate, Q_Gate, R_Gate;

  // Create P_Gate
  CreateGate(&P_Gate, P_type, X1, 0);
  int Y1 = P_Gate.GateValue(&P_Gate);

  // Create Q_Gate
  CreateGate(&Q_Gate, Q_type, X2, Y1);
  int Y2 = Q_Gate.GateValue(&Q_Gate);

  // Create R_Gate
  CreateGate(&R_Gate, R_type, X3, Y2);
  int Y3 = R_Gate.GateValue(&R_Gate);

  printf("%d %d %d\n", Y1, Y2, Y3);

  return 0;
}
