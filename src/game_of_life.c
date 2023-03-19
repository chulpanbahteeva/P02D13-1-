#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25

void read_file(int a[HEIGHT][WIDTH], int *flag);
void view(int a[HEIGHT][WIDTH], int *flag);
int neighbors(int a[HEIGHT][WIDTH], int x, int y);
void make_new(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]);
void swap(int a[HEIGHT][WIDTH], int b[HEIGHT][WIDTH]);
int speed(int *flag);

int main() {
    int current_array[HEIGHT][WIDTH] = {{current_array[0][0] = 0}};
    int new_array[HEIGHT][WIDTH] = {{new_array[0][0] = 0}};
    int flag = 0;
    rewind(stdin);
    read_file(current_array, &flag);
    int seed = speed(&flag);
    int cnt = 0;
    while (flag == 0) {
        if (9999 < seed && seed < 500001 && cnt < 1000) {
            view(current_array, &flag);
            usleep(seed);
            make_new(current_array, new_array);
            swap(current_array, new_array);
            cnt++;
        } else {
            flag = 1;
            break;
        }
    }
    return 0;
}

void read_file(int a[HEIGHT][WIDTH], int *flag) {
    int figure = 1;
    printf("Выбери начальную инициализацию (от 1 до 5): ");
    int b = scanf("%d", &figure);
    FILE *file = NULL;
    if (b != 1) {
        printf("Вводи целое число от 1 до 5!:)\n");
        *flag = 1;
    } else {
        if (figure == 1) {
            file = fopen("razmnozhitel.txt", "r");
        } else if (figure == 2) {
            file = fopen("HEART.txt", "r");
        } else if (figure == 3) {
            file = fopen("dolgozhitel.txt", "r");
        } else if (figure == 4) {
            file = fopen("parovoz.txt", "r");
        } else if (figure == 5) {
            file = fopen("gospers_gun.txt", "r");
        }
    }

    if (file == NULL) {
        printf("Файл не найден\n");
        *flag = 1;
    } else {
        char c;
        int cnt = 0;
        while ((c = getc(file)) != EOF) {
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
    fclose(file);
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
    int string;
    int column;
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
    int neighbor;
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

int speed(int *flag) {
    int res;
    int score;
    printf("Enter a speed from 1 to 5: ");
    scanf("%d", &score);
    if (score == 5) {
        res = 10000;
    } else if (score == 4) {
        res = 50000;
    } else if (score == 3) {
        res = 100000;
    } else if (score == 2) {
        res = 250000;
    } else if (score == 1) {
        res = 500000;
    } else
        *flag = 1;
    return res;
}