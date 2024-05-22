/*
25. 圖形結構
本題必須使用給定程式碼架構的struct及function pointer實作，否則將不予計分。

請參考給定的程式碼架構，使用 struct 定義以下結構：
Shape（圖形）, Circle（圓形）, Rectangle（矩形）, Square（正方形）,
Triangle（三角形）

圓形有半徑，矩形有長和寬，正方形有邊長，三角形有三個邊。
計算各個圖形的周長與面積，以及所有圖形的周長加總與面積加總。

圖形的程式碼架構參考範例如下：
#define ShapeText(TYPE) char name[10];
double (*perimeter)(struct TYPE*);
double (*area)(struct TYPE*)

typedef struct shape_s {
ShapeText(shape_s);
} shape_t;

typedef struct circle_s {
ShapeText(circle_s);
double radius;
} circle_t;

圖形的種類以代號輸入，對應圖形的代號如下：
C：圓形，結構內容具有 1 個 radius 屬性 (圓周率PI請使用3.14)
R：矩形，結構內容具有 1 個 length、1 個 width 屬性
S：正方形，結構內容具有 1 個 edge 屬性
T：三角形，結構內容具有 3 個 edge 屬性

三角形面積計算請使用海龍公式


【輸入說明】
第一行輸入N ( 2 <= N <= 5 )，代表圖形個數。
其後N行，輸入英文代號代表圖形種類，與該圖形種類的各個屬性(1<=屬性<=500)，屬性為整數，字元間以空格符號相隔開。

範例輸入：
2 (輸入2個圖形)
R 4 6 (輸入矩形，length=4，width=6)
S 3 (輸入正方型，edge=3)


【輸出說明】
第一行輸出第一個圖形的周長與面積，字元間以空格符號相隔。
第二行輸出第二個圖形的周長與面積，
以此類推，直到N行。
最後一行輸出圖形的周長總和與面積總和。

範例輸出：
20.00 24.00 (周長=(4+6)*2=20，面積=4*6=24)
12.00 9.00 (周長=3*4=12，面積=3*3= 9)
32.00 33.00 (周長總和=32，面積綜合=33)

備註：各個圖形的周長及面積需四捨五入到小數點後第2位，總和請先加總好再四捨五入。

【測試資料一】
輸入：
2
R 4 6
S 3

輸出：
20.00 24.00
12.00 9.00
32.00 33.00

【測試資料二】

輸入：
3
C 3
S 4
T 3 2 2

輸出：
18.84 28.26
16.00 16.00
7.00 1.98
41.84 46.24

【測試資料三】

輸入：
4
T 2 3 4
S 1
R 2 3
C 1

輸出：
9.00 2.90
4.00 1.00
10.00 6.00
6.28 3.14
29.28 13.04

【測試資料四】

輸入：
5
C 4
C 5
S 315
R 4 3
T 101 200 300

輸出：
25.12 50.24
31.40 78.50
1260.00 99225.00
14.00 12.00
601.00 1735.65
1931.52 101101.39

*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PI 3.14
#define ShapeText(TYPE)                                                        \
  char name[10];                                                               \
  double (*perimeter)(struct TYPE *);                                          \
  double (*area)(struct TYPE *);

typedef struct shape_s {
  ShapeText(shape_s);
} shape_t;

typedef struct circle_s {
  ShapeText(circle_s);
  double radius;
} circle_t;

typedef struct rectangle_s {
  ShapeText(rectangle_s);
  double length;
  double width;
} rectangle_t;

typedef struct square_s {
  ShapeText(square_s);
  double edge;
} square_t;

typedef struct triangle_s {
  ShapeText(triangle_s);
  double edge1;
  double edge2;
  double edge3;
} triangle_t;

double circle_perimeter(circle_t *circle) { return 2 * PI * circle->radius; }

double circle_area(circle_t *circle) {
  return PI * circle->radius * circle->radius;
}

double rectangle_perimeter(rectangle_t *rect) {
  return 2 * (rect->length + rect->width);
}

double rectangle_area(rectangle_t *rect) { return rect->length * rect->width; }

double square_perimeter(square_t *square) { return 4 * square->edge; }

double square_area(square_t *square) { return square->edge * square->edge; }

double triangle_perimeter(triangle_t *tri) {
  return tri->edge1 + tri->edge2 + tri->edge3;
}

double triangle_area(triangle_t *tri) {
  double s = (tri->edge1 + tri->edge2 + tri->edge3) / 2.0;
  return sqrt(s * (s - tri->edge1) * (s - tri->edge2) * (s - tri->edge3));
}

void CircleNew(circle_t *obj) {
  strcpy(obj->name, "circle");
  obj->perimeter = circle_perimeter;
  obj->area = circle_area;
}

void RectangleNew(rectangle_t *obj) {
  strcpy(obj->name, "rectangle");
  obj->perimeter = rectangle_perimeter;
  obj->area = rectangle_area;
}

void SquareNew(square_t *obj) {
  strcpy(obj->name, "square");
  obj->perimeter = square_perimeter;
  obj->area = square_area;
}

void TriangleNew(triangle_t *obj) {
  strcpy(obj->name, "triangle");
  obj->perimeter = triangle_perimeter;
  obj->area = triangle_area;
}

int main() {
  int n = 0;
  double total_perimeter = 0.0;
  double total_area = 0.0;

  scanf("%d", &n);
  getchar();
  // printf("n: %d\n", n);

  for (int i = 0; i < n; i++) {
    char shape = getchar();
    double p, a;
    // printf("shape: %c\n", shape);

    switch (shape) {
    case 'C': {
      circle_t circle;
      int radius;
      scanf("%d", &radius);
      circle.radius = (double)radius;
      // printf("radius: %1f\n", circle.radius);
      CircleNew(&circle);
      p = circle.perimeter(&circle);
      a = circle.area(&circle);
      printf("%.2lf %.2lf\n", p, a);
      break;
    }

    case 'R': {
      rectangle_t rectangle;
      int length, width;
      scanf("%d %d", &length, &width);
      rectangle.length = (double)length;
      rectangle.width = (double)width;
      // printf("l: %1f; w: %1f\n", rectangle.length, rectangle.width);
      RectangleNew(&rectangle);
      p = rectangle.perimeter(&rectangle);
      a = rectangle.area(&rectangle);
      printf("%.2lf %.2lf\n", p, a);
      break;
    }

    case 'S': {
      square_t square;
      int edge;
      scanf("%d", &edge);
      square.edge = (double)edge;
      // printf("edge: %1f\n", square.edge);
      SquareNew(&square);
      p = square.perimeter(&square);
      a = square.area(&square);
      printf("%.2lf %.2lf\n", p, a);
      break;
    }

    case 'T': {
      triangle_t triangle;
      int edge1, edge2, edge3;
      scanf("%d %d %d", &edge1, &edge2, &edge3);
      triangle.edge1 = (double)edge1;
      triangle.edge2 = (double)edge2;
      triangle.edge3 = (double)edge3;
      // printf("a: %1f, b: %1f, c: %1f\n", triangle.edge1,
      // triangle.edge2,triangle.edge3);
      TriangleNew(&triangle);
      p = triangle.perimeter(&triangle);
      a = triangle.area(&triangle);
      printf("%.2lf %.2lf\n", p, a);
      break;
    }
    }
    total_perimeter += p;
    total_area += a;
    getchar(); // 換行
    // printf("next~\n");
  }

  printf("%.2lf %.2lf\n", total_perimeter, total_area);
  return 0;
}