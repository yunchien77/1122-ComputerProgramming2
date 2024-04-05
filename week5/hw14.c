/*
014 大數運算

在此題目中，你需要將輸入的整數進行+、-、*的運算並輸出

【輸入說明】
第一行輸入第一個整數 (1<=整數位數<=100)
第一行輸入第二個整數 (1<=整數位數<=100)

範例輸入說明:
561651651641616585615168
8789896545646546546546546545

【輸出說明】
第一行輸出相加的結果 (1<=輸出位數<=201)
第一行輸出相減的結果 (1<=輸出位數<=201)
第一行輸出相乘的結果 (1<=輸出位數<=201)

範例輸出說明:
8790458197298188163132161713
-8789334893994904929960931377
4936859912621323139844513105778629278692394769994560

【測試資料一】
輸入：
4534534535995165165161651
99956651651651651651454535434

輸出：
99961186186187646816619697085
-99952117117115656486289373783
453256889016852581953231905042237629576284233717441534

【測試資料二】
輸入：
9999654174541651561654165415615616541654654
-6541651654165161651651651651465146654165444

輸出：
3458002520376489910002513764150469887489210
16541305828706813213305817067080763195820098
-65414254271969959029599286664161440719533332822203505376428354678452577994745228576376

【測試資料三】
輸入：
-5614651655165165165815165616351651
654155105016000000651651651651651651165

輸出：
654149490364344835486485836486035299514
-654160719667655165816817466817268002816
-3672853043112826841527601741547006206485802931827379657819289297423823415

【測試資料四】
輸入：
-8949849649644898999999999999999999
-564654654654444465416546489479874987854

輸出：
-564663604504094110315546489479874987853
564645704804794820517546489479874987855
5053574263129441237230267818966306202473428408593591329453510520125012146

【測試資料五】
輸入：
-4646546546546546546546546546465489789465999
4646546546546546546546546546465489789465999

輸出：
0
-9293093093093093093093093092930979578931998
-21590394809223638052466881294956856549579606708494079665257406619876008073585577068001

【測試資料六】
輸入：
654165131654616546445637525
-65416513546512315601325165453543

輸出：
-65415859381380660984778719816018
65417167711643970217871611091068
-42793202196540235706786376208911744547803275575410405001075

【測試資料七】
輸入：
8885613521515251653515135841561651651310631516
-8885613521515251653515135841561651651310631516

輸出：
0
17771227043030503307030271683123303302621263032
-78954127653734671559648880690313932932989188703994051754995126309891489120724557770732458256

*/

#include <math.h>
#include <stdio.h>

void add(int num1[], int num2[], int size1, int size2);
void sub(int num1[], int num2[], int size1, int size2);
void mul(int num1[], int num2[], int size1, int size2);
int compareIntArray(int arr1[], int size1, int arr2[], int size2);
void swapArrays(int arr1[], int arr2[], int size);
int isArrayAllZeros(int arr[], int size);

int main() {
  int num1[100] = {0}, num2[100] = {0};
  int size1 = 0, size2 = 0;
  int minus1 = 0, minus2 = 0; // 紀錄兩數是否為負數

  // 讀取第一個整數
  while (1) {
    char temp;
    scanf("%1c", &temp); // 逐個讀取一位數字
    if (temp == '\n')    // 如果讀到換行符號，則停止讀取
      break;
    if (temp == '-') {
      minus1 = 1;
      continue;
    }
    num1[size1] = temp - '0'; // 將讀取到的數字存放到陣列中
    size1++;                  // 增加陣列大小
  }
  /*
    printf("First integer: ");
    for (int i = 0; i < size1; i++)
      printf("%d", num1[i]);
    printf("\nSize of first integer: %d\n", size1);
  */

  // 讀取第二個整數
  /*
  while (1) {
    char temp;
    scanf("%1c", &temp); // 逐個讀取一位數字
    if (temp == '\n')    // 如果讀到換行符號，則停止讀取
      break;
    if (temp == '-') {
      minus2 = 1;
      continue;
    }
    num2[size2] = temp - '0'; // 將讀取到的數字存放到陣列中
    size2++;                  // 增加陣列大小
  }
  */

  // 讀取第二個整數
  while (1) {
    char temp;
    int result = scanf("%1c", &temp);
    if (result != EOF && temp != '\n') { // 成功讀取到整數且不是換行符號
      if (temp == '-') {
        minus2 = 1;
        continue;
      }
      num2[size2] = temp - '0';
      size2++;
    } else {
      break;
    }
  }

  /*
    printf("Second integer: ");
    for (int i = 0; i < size2; i++)
      printf("%d", num2[i]);
    printf("\nSize of second integer: %d\n", size2);

    printf("minus1: %d, minus2: %d\n", minus1, minus2);
  */
  if (minus1 == 0 && minus2 == 0) { // 兩數皆為正數
    add(num1, num2, size1, size2);
    sub(num1, num2, size1, size2);
    mul(num1, num2, size1, size2);
  } else if (minus1 == 1 && minus2 == 0) { // 第一個為負數，第二個為正數
    sub(num2, num1, size2, size1);         // 2-1
    printf("-");
    add(num1, num2, size1, size2); //-(1+2)
    printf("-");
    mul(num1, num2, size1, size2);         //-(1*2)
  } else if (minus1 == 0 && minus2 == 1) { // 第一個為正數，第二個為負數
    sub(num1, num2, size1, size2);         // 1-2
    add(num1, num2, size1, size2);         // 1+2
    printf("-");
    mul(num1, num2, size1, size2); //-(1*2)
  } else {                         // 兩數皆為負數
    printf("-");
    add(num1, num2, size1, size2); //-(1+2)
    sub(num2, num1, size2, size1); // 2-1
    mul(num1, num2, size1, size2); // 1*2
  }

  return 0;
}

void add(int num1[], int num2[], int size1, int size2) {
  int carry = 0;
  int max_size = (size1 > size2) ? size1 : size2;
  int result[201] = {0};

  for (int i = 0; i < max_size; i++) {
    int digit1 = (i < size1) ? num1[size1 - i - 1]
                             : 0; // 如果 i 超出了 num1 的範圍，將其設置為 0
    int digit2 = (i < size2) ? num2[size2 - i - 1]
                             : 0; // 如果 i 超出了 num2 的範圍，將其設置為 0
    int temp = digit1 + digit2 + carry;
    result[i] = temp % 10;
    carry = temp / 10;
  }

  if (carry != 0)
    result[max_size] = carry;
  else
    max_size--;

  int zero = isArrayAllZeros(result, max_size + 1);
  if (zero)
    printf("0");
  else {
    for (int i = max_size; i >= 0; i--) {
      printf("%d", result[i]);
    }
  }
  printf("\n");
}

void sub(int num1[], int num2[], int size1, int size2) {
  int trans = compareIntArray(num1, size1, num2, size2);
  int max_size = (size1 > size2) ? size1 : size2;
  int n1[201] = {0}, n2[201] = {0};
  for (int i = 0; i < size1; i++) {
    n1[i] = num1[i];
  }
  for (int i = 0; i < size2; i++) {
    n2[i] = num2[i];
  }
  if (trans == -1) {
    swapArrays(n1, n2, max_size);
    int t = size1;
    size1 = size2;
    size2 = t;
  }

  int borrow = 0;
  int result[201] = {0};
  for (int i = 0; i < max_size; i++) {
    int digit1 = (i < size1) ? n1[size1 - i - 1]
                             : 0; // 如果 i 超出了 num1 的範圍，將其設置為 0
    int digit2 = (i < size2) ? n2[size2 - i - 1]
                             : 0; // 如果 i 超出了 num2 的範圍，將其設置為 0
    int temp = digit1 - digit2;
    // printf("digit1:%d, digit2:%d, temp: %d\n", digit1, digit2, temp);
    if (temp < 0) {
      borrow = 10;
      n1[size1 - i - 2] -= 1;
      temp = digit1 - digit2 + borrow;
    }
    result[i] = temp;
  }
  int zero = isArrayAllZeros(result, max_size);
  if (zero)
    printf("0");
  else {
    if (trans == -1) {
      printf("-");
    }
    for (int i = max_size - 1; i >= 0; i--) {
      printf("%d", result[i]);
    }
  }

  printf("\n");
}

void mul(int num1[], int num2[], int size1, int size2) {
  int result[201] = {0};
  int carry = 0, count = 0;
  for (int i = 0; i < size2; i++) {
    for (int j = 0; j < size1; j++) {
      // printf("i: %d, j: %d, num1: %d, num2: %d, carry:%d\n", size2 - i - 1,
      //      size1 - j - 1, num1[size1 - j - 1], num2[size2 - i - 1], carry);
      int temp = num1[size1 - j - 1] * num2[size2 - i - 1] + carry;
      // printf("temp: %d\n", temp);
      int p = result[j + count] + (temp % 10);
      if (p >= 10)
        result[j + count + 1] += 1;

      result[j + count] = p % 10;

      carry = temp / 10;

      if (j == size1 - 1) {
        result[j + 1 + count] += carry;
        carry = 0;
        count++;
      }
      // printf("   ");
      // for (int k = size1 + size2 - 1; k >= 0; k--) {
      // printf("%d", result[k]);
      //}
      // printf("\n");
    }
  }
  for (int i = (size1 + size2 - 1); i >= 0; i--) {
    printf("%d", result[i]);
  }
  printf("\n");
}

int compareIntArray(int arr1[], int size1, int arr2[], int size2) {
  int minSize = (size1 < size2) ? size1 : size2;

  if (size1 < size2) {
    return -1;
  } else if (size1 > size2) {
    return 1;
  } else {
    for (int i = 1; i < minSize; i++) {
      if (arr1[i] < arr2[i]) {
        return -1;
      } else if (arr1[i] > arr2[i]) {
        return 1;
      }
    }
    return 0;
  }
}

void swapArrays(int arr1[], int arr2[], int size) {
  int temp;
  for (int i = 0; i < size; i++) {
    temp = arr1[i];
    arr1[i] = arr2[i];
    arr2[i] = temp;
  }
}

int isArrayAllZeros(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    if (arr[i] != 0) {
      return 0;
    }
  }
  return 1;
}