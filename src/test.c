#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 25

void read_file(int a[HEIGHT][WIDTH], int *flag);
void view(int a[HEIGHT][WIDTH], int *flag);
int neighbors(int a[HEIGHT][WIDTH], int x, int y);
void make_new(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]);
void swap(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]);

int main() {
  int current_array[HEIGHT][WIDTH] = {{current_array[0][0] = 0}};
  int new_array[HEIGHT][WIDTH] = {{new_array[0][0] = 0}};
  int flag = 0;
  char tap;

  read_file(current_array, &flag);
  while (flag == 0) {
    view(current_array, &flag);
    scanf("%c", &tap);
    if (tap == '\n') {
      make_new(current_array, new_array);
      swap(current_array, new_array);
    } else {
      flag = 1;
    }
  }
  printf("Goodbye!");
  return 0;
}

// void read_file(int a[HEIGHT][WIDTH], int *flag) {
//     FILE *file1 = fopen("HEART.txt", "r");
//     FILE *file2 = fopen("diamond.txt", "r");
//     FILE *file3 = fopen("CUSTOM.txt", "r");
//     FILE *file4 = fopen("letter.txt", "r");
//     FILE *file5 = fopen("GLIDER.txt", "r");

//     char c;
//     int cnt = 0;
//     if (file == NULL) {
//         printf("Cannot open file");
//         *flag = 1;
//     } else {
//         while ((c = getc(file)) != EOF){
//             if (c == '0') {
//                 a[cnt / WIDTH][cnt % WIDTH] = 0;
//                 cnt +=1;
//             }
//             if (c == '1') {
//                 a[cnt / WIDTH][cnt % WIDTH] = 1;
//                 cnt +=1;
//             }
//         }
//     }
//     fclose(file);
// }

void read_file(int a[HEIGHT][WIDTH], int *flag) {
  FILE *file1 = fopen("gospers_gun.txt", "r");
  // FILE *file2 = fopen("diamond.txt", "r");
  // FILE *file3 = fopen("CUSTOM.txt", "r");
  // FILE *file4 = fopen("letter.txt", "r");
  // FILE *file5 = fopen("GLIDER.txt", "r");

  char c;
  int cnt = 0;
  char vvod;
  printf("Choose the figure:\n1\n2\n3\n4\n5\n");
  vvod = getchar();
  if (vvod == '1') {
    if (file1 == NULL) {
      printf("Cannot open file.");
      *flag = 1;
    } else {
      while ((c = getc(file1)) != EOF) {
        if (c == '0') {
          a[cnt / WIDTH][cnt % WIDTH] = 0;
          cnt += 1;
        }
        if (c == '1') {
          a[cnt / WIDTH][cnt % WIDTH] = 1;
          cnt += 1;
        }
      }
    }
  }
  fclose(file1);
}

void view(int a[HEIGHT][WIDTH], int *flag) {
  int count = 0;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      if (a[i][j] == 0) {
        printf(" ");
      }
      if (a[i][j] == 1) {
        printf("*");
        count++;
      }
    }
    printf("\n");
  }
  if (count == 0) {
    *flag = 1;
  }
}

int neighbors(int a[HEIGHT][WIDTH], int x, int y) {
  int count = 0;
  int string = 0;
  int column = 0;
  for (int i = y - 1; i <= y + 1; i++) {
    for (int j = x - 1; j <= x + 1; j++) {
      if (i < 0) {
        string = HEIGHT - 1;
        column = j;
      } else if (i >= HEIGHT) {
        string = 0;
        column = j;
      } else if (j < 0) {
        column = WIDTH - 1;
        string = i;
      } else if (j >= WIDTH) {
        column = 0;
        string = i;
      } else {
        string = i;
        column = j;
      }
      count += a[string][column];
    }
  }
  count -= a[y][x];
  return count;
}

void make_new(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]) {
  int neighbor = 0;
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      neighbor = neighbors(a, j, i);
      if (a[i][j] == 0) {
        if (neighbor == 3) {
          b[i][j] = 1;
        }
      } else {
        if (neighbor < 2 || neighbor > 3) {
          b[i][j] = 0;
        }
        if (neighbor == 2 || neighbor == 3) {
          b[i][j] = 1;
        }
      }
    }
  }
}

void swap(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      a[i][j] = b[i][j];
    }
  }
}
