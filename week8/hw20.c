/*
020 字串處理

針對一篇英文文章
A，文章中全部均為英文字，以一個空白間隔，英文字母大小寫不同。輸入 2 個英文字
P、Q，操作文章:
(1) 將文章 A 中 P 以 Q 取代並輸出。
(2) 在文章 A 中 P 前插入 Q 並輸出。
(3) 將文章 A 中 P 字串刪除並輸出。
(4) 分析文章 A
所有英文字的頻率，依頻率由大自小排序，頻率相同則以英文字的字典順序由小自大排序(e.g.
That > This....)輸出。

【輸入說明】
第一行輸入文章A，1<=英文字數量<=50，英文字以一個空白間隔
第二行輸入英文單字P，1<=字母數量<=20
第三行輸入英文單字Q，1<=字母數量<=20

範例輸入說明:
This is a book That is a cook (文章A)
is (英文字P)
was (英文字Q)

【輸出說明】
第一行輸出操作1的結果，英文字以一個空白間隔
第二行輸出操作2的結果，英文字以一個空白間隔
第三行輸出操作3的結果，英文字以一個空白間隔
第四行~第N行輸出操作4的結果，英文字和頻率間以一個空白間隔

範例輸出說明:
This was a book That was a cook (將文章A中字is換成was)
This was is a book That was is a cook (將文章A中字is前面加上was)
This a book That a cook (將文章A中字is刪除)
a 2 (單字a出現2次，英文字和頻率間以一個空白間隔)
is 2 (單字is出現2次，英文字和頻率間以一個空白間隔)
That 1 (單字That出現1次，英文字和頻率間以一個空白間隔)
This 1 (單字This出現1次，英文字和頻率間以一個空白間隔)
book 1 (單字book出現1次，英文字和頻率間以一個空白間隔)
cook 1 (單字cook出現1次，英文字和頻率間以一個空白間隔)
(a排在is前面的原因是a比is還小，後面的That、This、book、cook也是同理)

【測試資料一】
輸入：
An apple can provide essential nutrients while a can preserves food freshness
can
CAN

輸出：
An apple CAN provide essential nutrients while a CAN preserves food freshness
An apple CAN can provide essential nutrients while a CAN can preserves food
freshness

An apple provide essential nutrients while a preserves food freshness
can 2
An 1
a 1
apple 1
essential 1
food 1
freshness 1
nutrients 1
preserves 1
provide 1
while 1

【測試資料二】
輸入：
Bird bird freedom bird embracing the sun bird of its wings a bird of light and
freedom
bird
dog

輸出：
Bird dog freedom dog embracing the sun dog of its wings a dog of light and
freedom

Bird dog bird freedom dog bird embracing the sun dog bird of its wings a dog
bird of light and freedom

Bird freedom embracing the sun of its wings a of light and freedom

bird 4
freedom 2
of 2
Bird 1
a 1
and 1
embracing 1
its 1
light 1
sun 1
the 1
wings 1

【測試資料三】
輸入：
Cryptographic key ensure secure communication across key Key
key
key

輸出：
Cryptographic key ensure secure communication across key Key
Cryptographic key key ensure secure communication across key key Key
Cryptographic ensure secure communication across Key
key 2
Cryptographic 1
Key 1
across 1
communication 1
ensure 1
secure 1

【測試資料四】
輸入：
code programmer diligently worked on the code ensuring its code before base it
with the project base
TEST
NOTHING

輸出：
code programmer diligently worked on the code ensuring its code before base it
with the project base code programmer diligently worked on the code ensuring its
code before base it with the project base code programmer diligently worked on
the code ensuring its code before base it with the project base

code 3
base 2
the 2
before 1
diligently 1
ensuring 1
it 1
its 1
on 1
programmer 1
project 1
with 1
worked 1

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 結構定義，用於存儲單字和其出現頻率
struct WordFreq {
  char word[21]; // 最大20個字母 + '\0'
  int freq;
};

// 比較函數，用於qsort排序
int compare(const void *a, const void *b) {
  const struct WordFreq *wordA = (struct WordFreq *)a;
  const struct WordFreq *wordB = (struct WordFreq *)b;
  if (wordA->freq != wordB->freq) {
    return wordB->freq - wordA->freq;
  } else {
    return strcmp(wordA->word, wordB->word);
  }
}

// 操作1：將文章中P以Q取代
void replaceWord(char *article, char *ans, char *p, char *q) {
  char *pos = article;
  while ((pos = strstr(pos, p)) != NULL) {
    // printf("%d\n", strlen(pos));
    // printf("%s\n", pos);
    if (*(pos - 1) != ' ') {
      pos += strlen(p);
      continue;
    }
    strncat(ans, article, strlen(article) - strlen(pos));
    article = (pos + strlen(p));
    // printf("%s\n", ans);
    strcat(ans, q);
    // printf("%s\n", ans);
    pos += strlen(q);
  }
  strcat(ans, article);
}

// 操作2：在文章中P前插入Q
void insertBefore(char *article, char *ans, char *p, char *q) {
  char *pos = article;
  while ((pos = strstr(pos, p)) != NULL) {
    if (*(pos - 1) != ' ') {
      pos += strlen(p);
      continue;
    }
    strncat(ans, article, strlen(article) - strlen(pos));
    article = (pos + strlen(p));

    strcat(ans, q);
    strcat(ans, " ");
    strcat(ans, p);
    pos += (strlen(q) + strlen(p)); // 移動pos到新插入字串的結尾
  }
  strcat(ans, article);
}

// 操作3：刪除文章中的P
void deleteWord(char *article, char *p) {
  char *pos = article;
  while ((pos = strstr(pos, p)) != NULL) {
    // 確保找到的單詞前後都是空格
    if ((pos == article || *(pos - 1) == ' ') &&
        (pos[strlen(p)] == ' ' || pos[strlen(p)] == '\0')) {
      // 如果單詞出現在句尾
      if (pos[strlen(p)] == '\0') {
        // 將上一個位置設為空字符結束
        *(pos - 1) = '\0';
      } else {
        // 將剩餘的文本向前移動
        // strcpy(pos, pos + strlen(p) + 1);
        memmove(pos, pos + strlen(p) + 1, strlen(pos + strlen(p)) + 1); // 刪除P
      }
    } else {
      // 如果單詞前後不是空格，則繼續尋找下一個
      pos += strlen(p);
    }
  }
}

int main() {
  char article[1001], p[21], q[21];
  fgets(article, sizeof(article), stdin);
  fgets(p, sizeof(p), stdin);
  fgets(q, sizeof(q), stdin);

  // 移除換行符
  article[strcspn(article, "\n")] = '\0';
  p[strcspn(p, "\n")] = '\0';
  q[strcspn(q, "\n")] = '\0';

  char article_1[1001] = "";
  char article_2[1001] = "";
  char article_3[1001] = "";
  char article_4[1001] = "";
  char article_set[strlen(article) + 1];

  // 操作1：將文章中P以Q取代並輸出
  replaceWord(article, article_1, p, q);
  printf("%s\n", article_1);

  // printf("sssssss %s\n", article);

  // 操作2：在文章中P前插入Q並輸出
  // strcpy(article_set, article);
  insertBefore(article, article_2, p, q);
  printf("%s\n", article_2);

  // 操作3：刪除文章中的P並輸出
  strcpy(article_set, article);
  deleteWord(article_set, p);
  printf("%s\n", article_set);

  // 操作4：分析文章中的單字頻率並輸出
  struct WordFreq wordFreq[50]; // 假設文章最多包含50個單字
  int wordCount = 0;

  char *token = strtok(article, " ");
  while (token != NULL) {
    // 檢查是否已經統計過該單字
    int i;
    for (i = 0; i < wordCount; i++) {
      if (strcmp(wordFreq[i].word, token) == 0) {
        wordFreq[i].freq++;
        break;
      }
    }
    // 如果是新單字，則添加到結構數組中
    if (i == wordCount) {
      strcpy(wordFreq[wordCount].word, token);
      wordFreq[wordCount].freq = 1;
      wordCount++;
    }
    token = strtok(NULL, " ");
  }

  // 將結構數組按照要求排序
  qsort(wordFreq, wordCount, sizeof(struct WordFreq), compare);

  // 輸出排序後的結果
  for (int i = 0; i < wordCount; i++) {
    printf("%s %d\n", wordFreq[i].word, wordFreq[i].freq);
  }

  return 0;
}
