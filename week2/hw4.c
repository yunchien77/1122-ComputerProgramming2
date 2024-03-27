/*
4. 有限狀態機

請使用有限狀態機判斷輸入值為以下何種型態:
1. 整數
2. 浮點數
3. 合法變數
4. 一般字串

1. 整數規則
整數除了負號必須所有字元皆為數字，且開頭不可為 0，但整數為 0 的狀況例外。
負號最多只有一個，且只能位於開頭。
長度介於 1~50。

2. 浮點數規則
浮點數除了小數點、負號，所有字元皆為數字。
開頭不可為小數點，結尾也不可為小數點，小數點最多只有一個。
開頭若為0，最多一個。
負號最多只有一個，且只能位於開頭。
長度介於 3~50。

3. 變數規則:
由大小寫英文字母、或數字、或 _ 組成。
開頭為大小寫英文字母、或 _ 。
長度介於 1~10。

4.一般字串
非以上三者，包含數字、大小寫英文、特殊符號@ # $ % & \ 等。
長度介於 1~50。


【輸入說明】
第一行輸入一個整數 N (1 <= N <= 7)，代表接下來輸入多少次字串
其後 N 行為輸入一字串，其長度為1~50字元。


範例輸入說明:
4 (N為4)
_abc
123
0.567
ghj/644

【輸出說明】
依據輸入字串，輸出對應值，
若字串為整數，輸出integer
若字串為浮點數，輸出float
若字串為變數，輸出variable
若以上情況皆不符合，輸出string

範例輸出說明:
variable (_abc符合變數規則)
integer (123符合整數規則)
float (0.567符合浮點數規則)
string (ghj/644不符合整數、變數、浮點數規則)

【測試資料一】
輸入：
4
_CisEZ_EMZ
CodeBlock
_1_0_1_1_0
TestP2P__


輸出：
variable
variable
variable
variable

【測試資料二】
輸入：
7
9874437434
5920000000
1234567890221126872995282646561238461235465481231
0
1634644357
-11155577788
6637373


輸出：
integer
integer
integer
integer
integer
integer
integer

【測試資料三】
4
3.14159265358979323
-1454864.720404254
1414.7414
987654154.000000000000000000000000000000000000

輸出：
float
float
float
float

【測試資料四】
輸入：
7
s35!@567-8!67*
-0
357346.
_sdfs.123
00
0.
1.234.75

輸出：
string
string
string
string
string
string
string

【測試資料五】
輸入：
5
_abc
456
10.654
-0.
_Pneumonoultramicroscopicsilicovolcanoconiosis1234

輸出：
variable
integer
float
string
string
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>

enum State { START, INTEGER, FLOAT, VARIABLE, STRING };

int isBegginingVariableChar(char c) { return isalpha(c) || c == '_'; }
int isVariableChar(char c) { return isalnum(c) || c == '_'; }

enum State checkType(char *str, int length) {
  enum State currentState = START;

  int i = 0;

  if (str[0] == '-') {
    if (length == 1 || !isdigit(str[1]))
      return STRING;
    if (length == 1 && isdigit(str[0])) // 0
      return INTEGER;
    currentState = INTEGER;
    i = 1;
  }

  int dotCount = 0; // 小數點數量
  for (; i < length; i++) {
    if (isdigit(str[i])) { // 數字
      if (currentState == START)
        currentState = INTEGER;
      else if (currentState == FLOAT)
        continue;
      else if (currentState == INTEGER)
        continue;
    } else if (str[i] == '.') { // 小數點
      if (currentState != INTEGER)
        return STRING;
      if (dotCount > 0)
        return STRING;
      dotCount++;
      currentState = FLOAT;
    } else if (str[i] == '@' || str[i] == '#' || str[i] == '$' ||
               str[i] == '%' || str[i] == '&' || str[i] == '/' ||
               str[i] == '\\') {
      return STRING;
    } else if (!isVariableChar(str[i])) {
      return STRING;
    } else {
      currentState = STRING;
    }
  }

  if (currentState == START || currentState == STRING) {
    if (!isBegginingVariableChar(str[0]))
      return STRING;
    if (length >= 1 && length <= 10) {
      currentState = VARIABLE;
    }
  } else if (currentState == INTEGER || currentState == FLOAT) {
    if (str[length - 1] == '.')
      return STRING;
    if (str[0] == '0' && length > 1 && str[1] != '.')
      return STRING;
    if (str[0] == '-' && str[1] == '0' && dotCount == 0)
      return STRING;
    if (str[0] == '-' && str[1] == '0' && str[2] == '0')
      return STRING;
  }

  if (currentState == FLOAT)
    if (length < 3)
      return STRING;

  return currentState;
}

int main() {
  int N;
  scanf("%d", &N);

  char input_str[N][51];
  enum State types[N];

  for (int i = 0; i < N; i++) {
    scanf("%s", input_str[i]);
    types[i] = checkType(input_str[i], strlen(input_str[i]));
  }

  for (int i = 0; i < N; i++) {
    switch (types[i]) {
    case INTEGER:
      printf("integer\n");
      break;
    case FLOAT:
      printf("float\n");
      break;
    case VARIABLE:
      printf("variable\n");
      break;
    case STRING:
      printf("string\n");
      break;
    default:
      break;
    }
  }

  return 0;
}
